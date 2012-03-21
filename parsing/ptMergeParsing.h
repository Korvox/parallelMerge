#ifndef _PTPARSING_
#define _PTPARSING_

#include <errno.h>
#include <string.h>
#include <limits.h>

#define PTMERGE_MAXARRAY 2048

/* Structure for the arguments processing */
typedef struct ptMerge_paras {
	unsigned char timing,
		numBytes;
	unsigned long numIndexes;
	void *toMerge;
} ptMerge_paras;

void ptMerge_fileErrorExit(FILE*);
void ptMerge_helpExit(char*);

void ptMerge_extractArray(char*, ptMerge_paras*);
unsigned long ptMerge_parseUnsignedLong(char*);
int * ptMerge_randomArray(unsigned long);
signed char ptMerge_parseArgs(ptMerge_paras, int, char**);

#endif
