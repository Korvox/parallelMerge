/* Serial Merge Parsing
 * @author Matthew Scheirer
 * @license GPL v3 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <omp.h>

#include "general/general.h"

#define BLOCKS 10

int main(int argc, char *argv[]) {
	if(argc != 2) {
		fprintf(stderr, "Usage: %s [numRands]\n",
			argv[0]);
		exit(EXIT_FAILURE);
	}

	unsigned int numRands = parseUnsignedInt(argv[1]);
	if(numRands == 0) {
		fprintf(stderr, "Parsing error on numRands");
		exit(EXIT_FAILURE);
	}

	double start = omp_get_wtime();
	int *randInts = randomInts(numRands);

	printf("Generated %u random integers in %f seconds\n",
		numRands, omp_get_wtime() - start);
	free(randInts);

	start = omp_get_wtime();
	long *randLongs = randomLongs(numRands);
	printf("Generated %u random longs in %f seconds\n",
		numRands, omp_get_wtime() - start);
	free(randLongs);

	start = omp_get_wtime();
	float *randFloats = randomFloats(numRands);
	printf("Generated %u random floats in %f seconds\n",
		numRands, omp_get_wtime() - start);
	free(randFloats);

	start = omp_get_wtime();
	double *randDoubles = randomDoubles(numRands);
	printf("Generated %u random doubles in %f seconds\n",
		numRands, omp_get_wtime() - start);
	free(randDoubles);

	exit(EXIT_SUCCESS);
}
