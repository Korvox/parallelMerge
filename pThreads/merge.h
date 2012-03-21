#ifndef _PTMERGE_
#define _PTMERGE_

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include "ptMergeParsing.h"

/* Structure to contain necessary thread data
 * for parallel merging. */
typedef struct ptMerge_t {
	void *start;
	unsigned long length;
	unsigned short size,
		numThreads;
} ptMerge_t;

unsigned short ptMerge_getNumThreads();
void ptMerge_setNumThreads(unsigned short);

void ptMerge_worker(void*);
void ptMerge(void*, unsigned long, unsigned short, unsigned short);

#endif
