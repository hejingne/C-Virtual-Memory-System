#ifndef __SIM_H__
#define __SIM_H__

#include "pagetable.h"


/* Simulated physical memory page frame size */
#define SIMPAGESIZE 16

extern size_t memsize;
extern bool debug;

extern size_t hit_count;
extern size_t miss_count;
extern size_t ref_count;
extern size_t evict_clean_count;
extern size_t evict_dirty_count;

/* We simulate physical memory with a large array of bytes */
extern char *physmem;

extern void (*ref_func)(pt_entry_t *);
extern int (*evict_func)(void);


#endif /* __SIM_H__ */
