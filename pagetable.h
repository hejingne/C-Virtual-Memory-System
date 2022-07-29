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

#ifndef __PAGETABLE_H__
#define __PAGETABLE_H__

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/types.h>


// User-level virtual addresses on a 64-bit Linux system are 48 bits in our
// traces, and the page size is 4096 (12 bits). We split the remaining 36 bits
// evenly into 3 parts, using 12 bits for each:
// - top-level (page directory pointer table - PDPT) index,
// - 2nd-level (page directory - PD) index,
// - 3rd-level (page table - PT) index.
//
// 47           35           23           11          0
// |------------|------------|------------|------------|
//   PDPT index    PD index     PT index    page offset

//NOTE: You are NOT allowed to modify the PTE format

#define PAGE_SHIFT 12
#define PAGE_SIZE  4096
#define PAGE_MASK  (~(PAGE_SIZE - 1))

//NOTE: You are NOT allowed to change flag bits defined below or add new ones

#define PAGE_VALID  0x1 // Valid bit in pdp or pde or pte, set if in memory
#define PAGE_DIRTY  0x2 // Dirty bit in pte, set if page has been modified
#define PAGE_REF    0x4 // Reference bit in pte, set if page has been referenced
#define PAGE_ONSWAP 0x8 // Set if page has been evicted to swap

#define PT_SHIFT   12 // Leaves top 36 bits of vaddr
#define PD_SHIFT   24 // Leaves top 24 bits of vaddr
#define PDPT_SHIFT 36 // Leaves top 12 bits of vaddr

#define PTRS_PER_PT   4096
#define PTRS_PER_PD   4096
#define PTRS_PER_PDPT 4096

#define PT_MASK (PTRS_PER_PT - 1)
#define PD_MASK (PTRS_PER_PD - 1)

#define PT_INDEX(x)   (((x) >> PT_SHIFT) & PT_MASK)
#define PD_INDEX(x)   (((x) >> PD_SHIFT) & PD_MASK)
#define PDPT_INDEX(x) ((x) >> PDPT_SHIFT)


typedef unsigned long vaddr_t;

// These defines allow us to take advantage of the compiler's typechecking

// Page directory pointer table entry (top-level)
typedef struct {
	uintptr_t pdp;
} pdpt_entry_t;

// Page directory entry (2nd-level)
typedef struct {
	uintptr_t pde;
} pd_entry_t;

// Page table entry (3rd-level)
typedef struct {
	unsigned int frame; // if valid bit == 1, physical frame holding vpage
	off_t swap_offset;     // offset in swap file of vpage, if any
} pt_entry_t;

#define INVALID_SWAP (off_t)-1


struct frame {
	bool in_use;    // true if frame is allocated, false if frame is free
	pt_entry_t *pte;// Pointer back to pagetable entry (pte) for page
	                // stored in this frame
};

/* The coremap holds information about physical memory.
 * The index into coremap is the physical page frame number stored
 * in the page table entry (pt_entry_t).
 */
extern struct frame *coremap;


void init_page_tables(void);
char *find_physpage(vaddr_t vaddr, char type);
void print_page_tables(void);
void free_page_tables(void);


// These may not need to do anything for some algorithms
void rand_init(void);
void fifo_init(void);
void clock_init(void);
void lru_init(void);
void mru_init(void);

// These may not need to do anything for some algorithms
void rand_cleanup(void);
void fifo_cleanup(void);
void clock_cleanup(void);
void lru_cleanup(void);
void mru_cleanup(void);

// These may not need to do anything for some algorithms
void rand_ref(pt_entry_t *);
void fifo_ref(pt_entry_t *);
void clock_ref(pt_entry_t *);
void lru_ref(pt_entry_t *);
void mru_ref(pt_entry_t *);

int rand_evict(void);
int fifo_evict(void);
int clock_evict(void);
int lru_evict(void);
int mru_evict(void);


#endif /* __PAGETABLE_H__ */
