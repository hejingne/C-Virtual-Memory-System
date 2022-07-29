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
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "pagetable.h"
#include "sim.h"
#include "swap.h"

//---------------------------------------------------------------------
// Bitmap definitions and functions to manage space in swapfile.
// We create a fixed-size swapfile, although it could be made larger
// on demand with a little effort.
//
// The bitmap code is modified from the OS/161 bitmap functions.

static const size_t bits_per_word = sizeof(size_t) * CHAR_BIT;
static const size_t word_all_bits = (size_t)-1;

static size_t nwords_for_nbits(size_t nbits)
{
	return (nbits + bits_per_word - 1) / bits_per_word;
}

struct bitmap {
	size_t nbits;
	size_t *words;
};

static int bitmap_init(struct bitmap *b, size_t nbits)
{
	size_t nwords = nwords_for_nbits(nbits);
	b->words = malloc(nwords * sizeof(size_t));
	if (!b->words) {
		return -1;
	}

	memset(b->words, 0, nwords * sizeof(size_t));
	b->nbits = nbits;

	// Mark any leftover bits at the end in use
	if (nwords > nbits / bits_per_word) {
		size_t idx = nwords - 1;
		size_t overbits = nbits - idx * bits_per_word;

		assert(nbits / bits_per_word == nwords - 1);
		assert(overbits > 0 && overbits < bits_per_word);

		for (size_t j = overbits; j < bits_per_word; ++j) {
			b->words[idx] |= ((size_t)1 << j);
		}
	}

	return 0;
}

static int bitmap_alloc(struct bitmap *b, size_t *index)
{
	size_t max_idx = nwords_for_nbits(b->nbits);

	for (size_t idx = 0; idx < max_idx; ++idx) {
		if (b->words[idx] != word_all_bits) {
			for (size_t offset = 0; offset < bits_per_word; ++offset) {
				size_t mask = (size_t)1 << offset;

				if ((b->words[idx] & mask) == 0) {
					b->words[idx] |= mask;
					*index = (idx * bits_per_word) + offset;
					assert(*index < b->nbits);
					return 0;
				}
			}
			assert(false);
		}
	}
	return -1;
}

static void bitmap_destroy(struct bitmap *b)
{
	free(b->words);
}

//---------------------------------------------------------------------
// Swap definitions and functions.

static int swapfd;
static struct bitmap swapmap;
static char fname[20];

void swap_init(size_t size)
{
	// Initialize the swap file
	strncpy(fname, "swapfile.XXXXXX", sizeof(fname));
	if ((swapfd = mkstemp(fname)) == -1) {
		perror("Failed to create temporary file for swap");
		exit(1);
	}

	// Initialize the bitmap
	if (bitmap_init(&swapmap, size) != 0) {
		perror("Failed to create bitmap for swap\n");
		exit(1);
	}
}

void swap_destroy(void)
{
	// Close and remove swapfile
	close(swapfd);
	unlink(fname);

	// Destroy bitmap
	bitmap_destroy(&swapmap);
}

// Read data into (simulated) physical memory 'frame' from 'offset'
// in swap file.
// Input:  frame - the physical frame number (not byte offset) in physmem
//         offset - the byte position in the swap file
// Return: 0 on success,
//         -errno on error or number of bytes read on partial read
//
int swap_pagein(unsigned int frame, off_t offset)
{
	assert(offset != INVALID_SWAP);

	// Get pointer to page data in (simulated) physical memory
	void *frame_ptr = &physmem[frame * SIMPAGESIZE];

	// Seek to position in swap file where this page was stored
	off_t pos = lseek(swapfd, offset, SEEK_SET);
	if (pos != offset) {
		assert(pos == (off_t)-1);
		perror("swap_pagein: failed to set read position");
		return -errno;
	}

	// Read page data from swapfile into memory
	ssize_t bytes_read = read(swapfd, frame_ptr, SIMPAGESIZE);
	if (bytes_read != SIMPAGESIZE) {
		fprintf(stderr, "swap_pagein: did not read whole page\n");
		return bytes_read;
	}
	return 0;
}

// Write data from (simulated) physical memory 'frame' to 'offset'
// in swap file. Allocates space in swap file for virtual page if needed.
// Input:  frame - the physical frame number (not byte offset in physmem)
//         offset - the byte position in the swap file
// Return: the offset where the data was written on success,
//         or INVALID_SWAP on failure
//
off_t swap_pageout(unsigned int frame, off_t offset)
{
	// Check if swap has already been allocated for this page
	if (offset == INVALID_SWAP) {
		size_t idx;
		if (bitmap_alloc(&swapmap, &idx) != 0) {
			fprintf(stderr, "swap_pageout: Could not allocate space in swapfile. "
			                "Try running again with a larger swapsize.\n");
			return INVALID_SWAP;
		}
		offset = idx * SIMPAGESIZE;
	}
	assert(offset != INVALID_SWAP);

	// Get pointer to page data in (simulated) physical memory
	void *frame_ptr = &physmem[frame * SIMPAGESIZE];

	// Seek to position in swap file where this page will be stored
	off_t pos = lseek(swapfd, offset, SEEK_SET);
	if (pos != offset) {
		assert(pos == (off_t)-1);
		perror("swap_pageout: failed to set write position");
		return INVALID_SWAP;
	}

	// Read page data from swapfile into memory
	ssize_t bytes_written = write(swapfd, frame_ptr, SIMPAGESIZE);
	if (bytes_written != SIMPAGESIZE) {
		fprintf(stderr, "swap_pageout: did not write whole page\n");
		return INVALID_SWAP;
	}
	return offset;
}
