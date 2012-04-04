/* Paramter handling, random number generation, and ranodm lists
 * @author Matthew Scheirer
 * @license GPL v3 */
 
#ifndef MGENERAL
#define MGENERAL

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <omp.h>

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

#define MULTIPLIER 48271
#define MODULUS 2147483647
#define FIRSTMULTI 7
#define JUMPLIMIT 22

#ifndef MPARAS
#define MPARAS
typedef struct {
	unsigned int length;
	unsigned short numThreads;
	unsigned char dataType;
	void *array;
} mergeParas;
#endif

int lehmerRandom(int);
int * generateSeeds(unsigned char);

int * randomInts(unsigned int);
long * randomLongs(unsigned int);
float * randomFloats(unsigned int);
double * randomDoubles(unsigned int);

unsigned int parseUnsignedInt(char*);
unsigned short parseUnsignedShort(char*);

void merge_helpExit(char*);
signed char merge_parseArgs(mergeParas*, int, char**);

#endif
