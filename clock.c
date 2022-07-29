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

#include "pagetable.h"
#include "sim.h"

static int clock_hand = 0;

/* Page to evict is chosen using the CLOCK algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */
int clock_evict(void)
{
	//TODO
    if (clock_hand == (int)memsize) {
        clock_hand = 0;
    }
	while (coremap[clock_hand].pte->frame & PAGE_REF) {
        coremap[clock_hand].pte->frame = coremap[clock_hand].pte->frame & ~PAGE_REF;
        clock_hand++;
        if (clock_hand == (int)memsize) {
            clock_hand = 0;
        }
    }
    return clock_hand++;
}

/* This function is called on each access to a page to update any information
 * needed by the CLOCK algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void clock_ref(pt_entry_t *pte)
{
	(void)pte;
	//TODO
}

/* Initialize any data structures needed for this replacement algorithm. */
void clock_init(void)
{
	//TODO
}

/* Cleanup any data structures created in clock_init(). */
void clock_cleanup(void)
{
	//TODO
}
