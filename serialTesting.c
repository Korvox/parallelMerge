/* Serial Merge Parsing
 * @author Matthew Scheirer
 * @license GPL v3 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "parsing/parsing.h"
#include "serial/serial.h"

#define BLOCKS 10

int main(int argc, char *argv[]) {
	if(argc != 2) {
		fprintf(stderr, "Usage: %s [numRands]\n",
			argv[0]);
		exit(EXIT_FAILURE);
	}

	unsigned long numRands = merge_parseUnsignedLong(argv[1]);
	if(numRands == 0) {
		fprintf(stderr, "Parsing error on numRands");
		exit(EXIT_FAILURE);
	}

	srand(123456789);
	int *randInts = merge_randomInts(numRands);

	//unsigned long todo = numRands + (BLOCKS - numRands % BLOCKS) % BLOCKS,
	//	i;

	/* This is the random longs array we generated, I print the
	 * values 10 at a time to reduce system calls and make the
	 * resulting grid easier to read */ /*
	for(i = 0; i < todo; i+= BLOCKS) {
		printf("%i %i %i %i %i\n%i %i %i %i %i\n",
			randInts[i], randInts[i + 1], randInts[i + 2],
			randInts[i + 3], randInts[i + 4], randInts[i + 5],
			randInts[i + 6], randInts[i + 7], randInts[i + 8],
			randInts[i + 9]);
	}
	putc('\n', stdout); */

	time_t start = time(NULL);
	int *intRet = serialSort((void*) randInts, numRands, MINT);
	printf("Int array of\t%lu elements merged serially in %i seconds\n",
		numRands, time(NULL) - start);

	/* This is the random longs array we generated again, and it
	 * should not have changed from calling serialSort - serial sort
	 * intReturns the sorted version of it, because it already has to
	 * allocate the space, the caller can manually copy it back
	 * over if it really wants. */ /*
	for(i = 0; i < todo; i+= BLOCKS) {
		printf("%i %i %i %i %i\n%i %i %i %i %i\n",
			randInts[i], randInts[i + 1], randInts[i + 2],
			randInts[i + 3], randInts[i + 4], randInts[i + 5],
			randInts[i + 6], randInts[i + 7], randInts[i + 8],
			randInts[i + 9]);
	}
	putc('\n', stdout); */
	free(randInts);

	for(unsigned long i = 1; i < numRands; i++) {
		if(intRet[i - 1] > intRet[i])
			printf("Indexes %lu and %lu are out of place\n", i - 1, i);
	}

	/* This "should" be the previous array, sorted.  The results when
	 * run with the regular build ARE sorted longs, but they are different
	 * numbers from what the original array contained.  I think?  Something seems
	 * off with the first array, because the values are never very large.  And they
	 * are made with rand().  So I think the recursive sort IS working, but the
	 * printing of the original array is bad? */ /*
	for(i = 0; i < todo; i+= BLOCKS) {
		printf("%i %i %i %i %i\n%i %i %i %i %i\n",
			intRet[i], intRet[i + 1], intRet[i + 2],
			intRet[i + 3], intRet[i + 4], intRet[i + 5],
			intRet[i + 6], intRet[i + 7], intRet[i + 8],
			intRet[i + 9]);
	}
	putc('\n', stdout); */
	free(intRet);

	srand(123456789);
	long *randLongs = merge_randomLongs(numRands);
	start = time(NULL);
	long *longRet = serialSort((void*) randLongs, numRands, MLONG);
	printf("Long array of\t%lu elements merged serially in %i seconds\n",
		numRands, time(NULL) - start);
	free(randLongs);
	for(unsigned long i = 1; i < numRands; i++) {
		if(longRet[i - 1] > longRet[i])
			printf("Indexes %lu and %lu are out of place\n", i - 1, i);
	}
	free(longRet);

	srand(123456789);
	float *randFloats = merge_randomFloats(numRands);
	start = time(NULL);
	float *floatRet = serialSort((void*) randFloats, numRands, MFLOAT);
	printf("Float array of\t%lu elements merged serially in %i seconds\n",
		numRands, time(NULL) - start);
	free(randFloats);
	for(unsigned long i = 1; i < numRands; i++) {
		if(floatRet[i - 1] > floatRet[i])
			printf("Indexes %lu and %lu are out of place\n", i - 1, i);
	}
	free(floatRet);

	srand(123456789);
	double *randDoubles = merge_randomDoubles(numRands);
	start = time(NULL);
	double *doubleRet = serialSort((void*) randDoubles, numRands, MDOUBLE);
	printf("Double array of\t%lu elements merged serially in %i seconds\n",
		numRands, time(NULL) - start);
	free(randDoubles);
	for(unsigned long i = 1; i < numRands; i++) {
		if(doubleRet[i - 1] > doubleRet[i])
			printf("Indexes %lu and %lu are out of place\n", i - 1, i);
	}
	free(doubleRet);
	exit(EXIT_SUCCESS);
}
