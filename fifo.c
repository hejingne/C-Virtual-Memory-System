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

static int victim_frame_num = 0;

/* Page to evict is chosen using the FIFO algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */
int fifo_evict(void)
{
	//TODO
    if (victim_frame_num == (int)memsize) {
        victim_frame_num = 0;
    }
    return victim_frame_num++;
}

/* This function is called on each access to a page to update any information
 * needed by the FIFO algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void fifo_ref(pt_entry_t *pte)
{
    (void)pte;
	//TODO
}

/* Initialize any data structures needed for this replacement algorithm. */
void fifo_init(void)
{
	//TODO
}

/* Cleanup any data structures created in fifo_init(). */
void fifo_cleanup(void)
{
	//TODO
}
