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
#include <stdlib.h>


struct node {
    int data;   // stores the frame number
    struct node *next;  // next is the less recently used frame compared to this node's frame
    struct node *prev;  // prev is the more recently used frame compared to this node's frame
};

struct node *stack;
struct node *top = NULL;   // pointer to the top of stack (MRU frame)
struct node *bottom = NULL;   // pointer to the bottom of stack (LRU frame)


/* Page to evict is chosen using the accurate MRU algorithm.
 * Returns the page frame number (which is also the index in the coremap)
 * for the page that is to be evicted.
 */
int mru_evict(void)
{
	//TODO
    struct node *victim = &stack[top->data];

    if (top->next == NULL) {    // If stack has only 1 node
        bottom = NULL;
    } else {
        (top->next)->prev = NULL;
    }
    top = top->next;

    victim->prev = NULL;    // Set top's prev and next to NULL
    victim->next = NULL;    // to represent the removal of the top of stack
    return victim->data;
}

/* This function is called on each access to a page to update any information
 * needed by the MRU algorithm.
 * Input: The page table entry for the page that is being accessed.
 */
void mru_ref(pt_entry_t *pte)
{
	//TODO
    int frame_num = pte->frame >> PAGE_SHIFT;
    struct node *ref = &stack[frame_num];

    if (top != ref) {  // If top is referenced (a Hit), do nothing
        ref->data = frame_num;

        if (top == NULL) {     // If stack is empty
            bottom = ref;   // Mark the bottom of stack
        } else {
            top->prev = ref;
        }

        if (ref->prev != NULL) {
            (ref->prev)->next = ref->next;
            if (ref->next != NULL) {
                (ref->next)->prev = ref->prev;
            }
            if (bottom == ref) {
                bottom = ref->prev;   // If bottom is referenced (a Hit), update bottom
            }
            ref->prev = NULL;
        }

        ref->next = top;
        top = ref;    // Update top
    }
}

/* Initialize any data structures needed for this replacement algorithm. */
void mru_init(void)
{
	//TODO
    stack = calloc(memsize, sizeof(struct node));
}

/* Cleanup any data structures created in mru_init(). */
void mru_cleanup(void)
{
	//TODO
    free(stack);
}
