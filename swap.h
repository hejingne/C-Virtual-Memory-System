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

#ifndef __SWAP_H__
#define __SWAP_H__

#include <sys/types.h>


// Swap functions for use in other files

void swap_init(size_t size);
void swap_destroy(void);

int swap_pagein(unsigned int frame, off_t offset);
off_t swap_pageout(unsigned int frame, off_t offset);


#endif /* __SWAP_H__ */
