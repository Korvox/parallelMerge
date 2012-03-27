/* Serial Merge Parsing
 * @author Matthew Scheirer
 * @license GPL v3 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "parsing/parsing.h"
#include "serial/serial.h"

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
	time_t start = time(NULL);
	serialSort((void*) randLongs, numRands, MLONG);
	printf("Long array of %lu elements merged serially in %f seconds\n",
		numRands, time(NULL) - start);
	free(randLongs);

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

	exit(EXIT_SUCCESS);
}
