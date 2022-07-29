/*
 * This code is provided solely for the personal and private use of students
 * taking the CSC369H course at the University of Toronto. Copying for purposes
 * other than this use is expressly prohibited. All forms of distribution of
 * this code, including but not limited to public repositories on GitHub,
 * GitLab, Bitbucket, or any other online platform, whether as given or with
 * any changes, are expressly prohibited.
 *
 * Authors: Andrew Peterson, Karen Reid, Alexey Khrabrov
 *
 * All of the files in this directory and all subdirectories are:
 * Copyright (c) 2019, 2021 Karen Reid
 */

#include <assert.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sim.h"
#include "pagetable.h"
#include "swap.h"


// Define global variables declared in sim.h
size_t memsize = 0;
bool debug = false;
char *physmem = NULL;
struct frame *coremap = NULL;

/* Each eviction algorithm is represented by a structure with its name
 * and three functions.
 */
struct functions {
	const char *name;         // String name of eviction algorithm
	void (*init)(void);       // Initialize any data needed by alg
	void (*cleanup)(void);    // Cleanup any data initialized in init()
	void (*ref)(pt_entry_t *);// Called on each reference
	int (*evict)(void);       // Called to choose victim for eviction
};

/* The algs array gives us a mapping between the name of an eviction
 * algorithm as given in a command line argument, and the function to
 * call to select the victim page.
 */
static struct functions algs[] = {
	{ "rand", rand_init, rand_cleanup, rand_ref, rand_evict },
	{ "fifo", fifo_init, fifo_cleanup, fifo_ref, fifo_evict },
	{ "clock", clock_init, clock_cleanup, clock_ref, clock_evict },
	{ "lru", lru_init, lru_cleanup, lru_ref, lru_evict },
	{ "mru", mru_init, mru_cleanup, mru_ref, mru_evict },
};
static size_t num_algs = sizeof(algs) / sizeof(algs[0]);

static void (*init_func)() = NULL;
static void (*cleanup_func)() = NULL;

void (*ref_func)(pt_entry_t *) = NULL;
int (*evict_func)() = NULL;


/* An actual memory access based on the vaddr from the trace file.
 *
 * The find_physpage() function is called to translate the virtual address
 * to a (simulated) physical address -- that is, a pointer to the right
 * location in physmem array. The find_physpage() function is responsible for
 * everything to do with memory management - including translation using the
 * pagetable, allocating a frame of (simulated) physical memory (if needed),
 * evicting an existing page from the frame (if needed) and reading the page
 * in from swap (if needed).
 *
 * We then check that the memory has the expected content (just a copy of the
 * virtual address) and, in case of a write reference, increment the version
 * counter.
 */
static void access_mem(char type, vaddr_t vaddr, size_t linenum)
{
	char *memptr = find_physpage(vaddr, type);
	size_t *versionptr = (size_t *)memptr;
	vaddr_t *checkaddr = (vaddr_t *)(memptr + sizeof(size_t));

	if (*checkaddr != (vaddr & PAGE_MASK)) {
		fprintf(stderr, "Error: unexpected value in simulated page: %zu != %zu"
		        " (trace line %zu)\n", *checkaddr, vaddr, linenum);
        printf("=== check: %zu , vaddr: %zu, memptr: %s", *checkaddr, vaddr, memptr); //test
	}

	if ((type == 'S') || (type == 'M')) {
		// write access to page, increment version number
		(*versionptr)++;
	}
}

static void replay_trace(FILE *f)
{
	char line[256];
	size_t linenum = 0;
	while (fgets(line, sizeof(line), f)) {
		++linenum;
		if (line[0] == '=') {
			continue;
		}

		vaddr_t vaddr;
		char type;
		if (sscanf(line, "%c %zx", &type, &vaddr) != 2) {
			fprintf(stderr, "Invalid trace line %zu: %s\n", linenum, line);
			exit(1);
		}
		if (debug) {
			printf("%c %lx\n", type, vaddr);
		}
		access_mem(type, vaddr, linenum);
	}
}


int main(int argc, char *argv[])
{
	char *tracefile = NULL;
	size_t swapsize = 0;
	char *replacement_alg = NULL;
	const char *usage = "USAGE: sim -f tracefile -m memorysize -s swapsize -a algorithm\n";

	int opt;
	while ((opt = getopt(argc, argv, "f:m:a:s:")) != -1) {
		switch (opt) {
		case 'f':
			tracefile = optarg;
			break;
		case 'm':
			memsize = strtoul(optarg, NULL, 10);
			break;
		case 'a':
			replacement_alg = optarg;
			break;
		case 's':
			swapsize = strtoul(optarg, NULL, 10);
			break;
		default:
			fprintf(stderr, "%s", usage);
			return 1;
		}
	}
	if (!tracefile || !memsize || !swapsize || !replacement_alg) {
		fprintf(stderr, "%s", usage);
		return 1;
	}

	FILE *tfp = fopen(tracefile, "r");
	if (!tfp) {
		perror(tracefile);
		return 1;
	}

	// Initialize main data structures for simulation.
	// This happens before calling the replacement algorithm init function
	// so that the init_func can refer to the coremap if needed.
	coremap = calloc(memsize, sizeof(struct frame));
	physmem = calloc(memsize, SIMPAGESIZE);
	swap_init(swapsize);
	init_page_tables();

	for (size_t i = 0; i < num_algs; ++i) {
		if (strcmp(algs[i].name, replacement_alg) == 0) {
			init_func = algs[i].init;
			cleanup_func = algs[i].cleanup;
			ref_func = algs[i].ref;
			evict_func = algs[i].evict;
			break;
		}
	}
	if (!evict_func) {
		fprintf(stderr, "Error: invalid replacement algorithm - %s\n",
				replacement_alg);
		return 1;
	}

	// Call replacement algorithm's init_func before replaying trace.
	init_func();
	replay_trace(tfp);
	if (debug) {
		print_page_tables();
	}
	cleanup_func();

	// Cleanup data structures and remove temporary swapfile
	free(coremap);
	free(physmem);
	swap_destroy();
	free_page_tables();

	printf("\n");
    printf("Hit rate: %.4f\n", ((double)hit_count / ref_count) * 100.0);
	printf("Hit count: %zu\n", hit_count);
    printf("Miss rate: %.4f\n", ((double)miss_count / ref_count) * 100.0);
	printf("Miss count: %zu\n", miss_count);
    printf("Total references : %zu\n\n\n", ref_count);
    printf("Overall evictions count: %zu\n", evict_clean_count + evict_dirty_count);
	printf("Clean evictions count: %zu\n", evict_clean_count);
	printf("Dirty evictions count: %zu\n", evict_dirty_count);

	return 0;
}
