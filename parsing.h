/* Parallel Merge Parsing
 * @author Matthew Scheirer
 * @license GPL v3 */

#ifndef _PTPARSING_
#define _PTPARSING_

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>

/* Max # element bound.  Consider this * size of container
 * for size of array */
#define MERGE_MAXARRAY 8192

/* These macros are used to denote the type of elements in array */
#define MLONG 0
#define MLONGLONG 1
#define MDOUBLE 2

/* Structure to contain necessary thread data
 * for parallel merging. */
typedef struct merge_t {
	void *start;
	unsigned long length;
	unsigned short size,
		numThreads;
} merge_t;

/* Structure for the arguments processing */
typedef struct mergeParas {
	unsigned char dataType = 0;
	unsigned long length,
		numThreads = 1;
	void *array;
} mergeParas;

void merge_fileErrorExit(FILE*);
void merge_helpExit(char*);

void merge_extractArray(char*, mergeParas*);
unsigned long merge_parseUnsignedLong(char*);
int * merge_randomArray(unsigned long);
signed char merge_parseArgs(mergeParas*, int, char**);

#endif
