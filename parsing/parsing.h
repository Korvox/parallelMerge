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

/* Max digits allowed to be parsed from a float or double */
#define MPARSEFLOATMAX 255

/* These macros are used to denote the type of elements in array */
#ifndef MINT
#define MINT 0
#endif
#ifndef MLONG
#define MLONG 1
#endif
#ifndef MFLOAT
#define MFLOAT 2
#endif
#ifndef MDOUBLE
#define MDOUBLE 3
#endif

#ifndef MERGEPARAS
#define MERGEPARAS
typedef struct {
	unsigned char dataType;
	unsigned long length;
	unsigned short numThreads;
	void *array;
} mergeParas;
#endif

void merge_fileErrorExit(FILE*);
void merge_helpExit(char*);

int * merge_extractIntArray(char*);
long * merge_extractLongArray(char*);
float * merge_extractFloatArray(char*);
double * merge_extractDoubleArray(char*);

int * merge_randomInts(unsigned long);
long * merge_randomLongs(unsigned long);
float * merge_randomFloats(unsigned long);
double * merge_randomDoubles(unsigned long);

unsigned long merge_parseUnsignedLong(char*);
signed char merge_parseArgs(mergeParas*, int, char**);

#endif
