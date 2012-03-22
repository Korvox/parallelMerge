#ifndef _PTMERGE_
#define _PTMERGE_

#include "../parsing.h"
#include <semaphore.h>
#include <time.h>

/* Structure to contain necessary thread data
 * for parallel merging. */
typedef struct merge_t {
	void *start;
	unsigned long length;
	unsigned short size,
		numThreads;
} merge_t;

unsigned short merge_getNumThreads();
void merge_setNumThreads(unsigned short);

void merge_serialSort(void *, unsigned long, unsigned char);
void merge_worker(void*);
void * merge(mergeParas*);

#endif
