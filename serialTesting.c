/* Serial Merge Parsing
 * @author Matthew Scheirer
 * @license GPL v3 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "parsing/parsing.h"
#include "serial/serial.h"

#define BLOCKX 10

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
	long *randLongs = merge_randomLongs(numRands);

	int todo = numRands + (BLOCKX - numRands % BLOCKX) % BLOCKX,
		i;

	/* This is the random longs array we generated, I print the
	 * values 10 at a time to reduce system calls and make the
	 * resulting grid easier to read */
	for(i = 0; i < todo; i+= BLOCKX) {
		printf("%li %li %li %li %li %li %li %li %li %li\n",
			randLongs[i], randLongs[i + 1], randLongs[i + 2],
			randLongs[i + 3], randLongs[i + 4], randLongs[i + 5],
			randLongs[i + 6], randLongs[i + 7], randLongs[i + 8],
			randLongs[i + 9]);
	}
	putc('\n', stdout);
	
	time_t start = time(NULL);
	long *ret = serialSort((void*) randLongs, numRands, MLONG);
	printf("Long array of %lu elements merged serially in %.2f seconds\n",
		numRands, time(NULL) - start);

	/* This is the random longs array we generated again, and it
	 * should not have changed from calling serialSort - serial sort
	 * returns the sorted version of it, because it already has to
	 * allocate the space, the caller can manually copy it back
	 * over if it really wants. */
	for(i = 0; i < todo; i+= BLOCKX) {
		printf("%li %li %li %li %li %li %li %li %li %li\n",
			randLongs[i], randLongs[i + 1], randLongs[i + 2],
			randLongs[i + 3], randLongs[i + 4], randLongs[i + 5],
			randLongs[i + 6], randLongs[i + 7], randLongs[i + 8],
			randLongs[i + 9]);
	}
	putc('\n', stdout);
		
	free(randLongs);

	/* This "should" be the previous array, sorted.  The results when
	 * run with the regular build ARE sorted longs, but they are different
	 * numbers from what the original array contained.  I think?  Something seems
	 * off with the first array, because the values are never very large.  And they
	 * are made with rand().  So I think the recursive sort IS working, but the
	 * printing of the original array is bad? */
	for(i = 0; i < todo; i+= BLOCKX) {
		printf("%li %li %li %li %li %li %li %li %li %li\n",
			ret[i], ret[i + 1], ret[i + 2],
			ret[i + 3], ret[i + 4], ret[i + 5],
			ret[i + 6], ret[i + 7], ret[i + 8],
			ret[i + 9]);
	}
	putc('\n', stdout);
	free(ret);
	
	/* UNCOMMENT THIS TO TEST THE OTHER IMPLEMENTATIONS
	srand(123456789);
	long long *randLongLongs = merge_randomLongLongs(numRands);
	start = time(NULL);
	serialSort((void*) randLongLongs, numRands, MLONGLONG);
	printf("long long array of %lu elements merged serially in %f seconds\n",
		numRands, time(NULL) - start);
	free(randLongLongs);

	srand(123456789);
	float *randFloats = merge_randomFloats(numRands);
	start = time(NULL);
	serialSort((void*) randFloats, numRands, MFLOAT);
	printf("Float array of %lu elements merged serially in %f seconds\n",
		numRands, time(NULL) - start);
	free(randFloats);

	srand(123456789);
	double *randDoubles = merge_randomDoubles(numRands);
	start = time(NULL);
	serialSort((void*) randDoubles, numRands, MDOUBLE);
	printf("Double array of %lu elements merged serially in %f seconds\n",
		numRands, time(NULL) - start);
	free(randDoubles);
	*/
	exit(EXIT_SUCCESS);
}
