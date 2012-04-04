/* Paramter handling, random number generation, and ranodm lists
 * @author Matthew Scheirer
 * @license GPLv3 */
 
#include "general.h"

/* Maximum number of elements we allow to be generated.  This number is
 * 2^30 / 8 (approximately a gigabyte divided by byte size of doubles. */
const int merge_sizeLimit = 134217728,
	q = MODULUS / MULTIPLIER,
	r = MODULUS % MULTIPLIER;

/* This inline random function prevents integer overflow */
inline int lehmerRandom(int seed) {
	seed = MULTIPLIER * (seed % q) - r * (seed / q);
	return seed > 0 ? seed : seed + MODULUS;
}

/* Generate numSeeds seed values, such that there are a total of
 * MODULUS - 1 / numSeeds random numbers between each seed in the rng */
int * generateSeeds(unsigned char numSeeds) {
	if(numSeeds > JUMPLIMIT) {
		fprintf(stderr, "Can only generate up to %d seed values.\n",
			JUMPLIMIT);
		return NULL;
	}
	int *seeds = malloc(numSeeds * sizeof(int));
	unsigned long jumpMultipler = fmod(pow(FIRSTMULTI, numSeeds), MODULUS);
	for(unsigned char counter = 0; counter < numSeeds; counter++)
		seeds[counter] = jumpMultipler * (counter + 1) % (MODULUS - 1);
	return seeds;
}

int * randomInts(unsigned int length) {
	if(length > merge_sizeLimit) {
		fprintf(stderr, "Can't generate arrays larger than %i\n", 
			merge_sizeLimit);
		return NULL;
	}
	
	unsigned char numProcs = omp_get_num_procs();
		//remainder = length % numProcs;
	int *seeds = generateSeeds(numProcs),
		*array = malloc(length * sizeof(int));
	unsigned int counter;
#pragma omp parallel for
	for(counter = 0; counter < length; counter++) {
		unsigned char index = omp_get_thread_num();
		array[counter] = seeds[index] = lehmerRandom(seeds[index]);
	}
	return array;
}

long * randomLongs(unsigned int length) {
	if(length > merge_sizeLimit) {
		fprintf(stderr, "Can't generate arrays larger than %i\n", 
			merge_sizeLimit);
		return NULL;
	}
	
	unsigned char numProcs = omp_get_num_procs();
	int *seeds = generateSeeds(numProcs);
	long *array = malloc(length * sizeof(long));
	unsigned int counter;
	
#pragma omp parallel for
	for(counter = 0; counter < length; counter++) {
		unsigned char index = omp_get_thread_num();
		array[counter] = seeds[index] = lehmerRandom(seeds[index]);
		array[counter] *= seeds[index] = lehmerRandom(seeds[index]);
	}
	return array;
}

/* Generate a random array of floats of length length */
float * randomFloats(unsigned int length) {
	if(length > merge_sizeLimit) {
		fprintf(stderr, "Can't generate arrays larger than %i\n", 
			merge_sizeLimit);
		return NULL;
	}
	
	unsigned char numProcs = omp_get_num_procs();
	int *seeds = generateSeeds(numProcs);
	float *array = malloc(length * sizeof(float));
	unsigned int counter;
	
#pragma omp parallel for
	for(counter = 0; counter < length; counter++) {
		unsigned char index = omp_get_thread_num();
		array[counter] = seeds[index] = lehmerRandom(seeds[index]);
		array[counter] /= seeds[index] = lehmerRandom(seeds[index]);
	}
	return array;
}

/* Generate a random array of doubles of length length */
double * randomDoubles(unsigned int length) {
	if(length > merge_sizeLimit) {
		fprintf(stderr, "Can't generate arrays larger than %i\n", 
			merge_sizeLimit);
		return NULL;
	}
	
	unsigned char numProcs = omp_get_num_procs();
	int *seeds = generateSeeds(numProcs);
	double *array = malloc(length * sizeof(double));
	unsigned int counter;
	
#pragma omp parallel for
	for(counter = 0; counter < length; counter++) {
		unsigned char index = omp_get_thread_num();
		array[counter] = seeds[index] = lehmerRandom(seeds[index]);
		array[counter] /= seeds[index] = lehmerRandom(seeds[index]);
		array[counter] *= seeds[index] = lehmerRandom(seeds[index]);
	}
	return array;
}

/* Replacement for atoi to parse an unsigned int length
 * Returns 0 on error */
unsigned int parseUnsignedInt(char *source) {
	unsigned int result = 0;
	unsigned char parse,
		counter = 0;

	while((parse = source[counter++]) != '\0') {
		/* If we have an invalid char anywhere */
		if(parse < '0' || parse > '9') {
			fprintf(stderr, "Invlaid char in parsed int %c\n", parse);
			return 0;
		}

		/* Covert parse into its true digit value */
		parse -= '0';

		if(result * 10 + parse > UINT_MAX) {
			fprintf(stderr, "Given input %s overflows unsigned int %d %u\n",
				source, result * 10 + parse, UINT_MAX);
			return 0;
		}
		
		result = result * 10 + parse;
	}
	return result;
}

unsigned short parseUnsignedShort(char *source) {
	unsigned short result = 0;
	unsigned char parse,
		counter = 0;

	while((parse = source[counter++]) != '\0') {
		/* If we have an invalid char anywhere */
		if(parse < '0' || parse > '9') {
			fprintf(stderr, "Invlaid char in parsed long %c\n", parse);
			return 0;
		}

		/* Covert parse into its true digit value */
		parse -= '0';

		if(result * 10 + parse > USHRT_MAX) {
			fprintf(stderr, "Given input %s overflows unsigned short %d %u\n",
				source, result * 10 + parse, USHRT_MAX);
			return 0;
		}
		
		result = result * 10 + parse;
	}
	return result;
}

/* This error prints the usage of merge */
void merge_helpExit(char *callingName) {
	printf("Usage: %s [flags] [listsize]\n\
	flags:\t-t [type #], -n [threads], -r [time sorting]\n\
	-t:\tType of elements.  If not specified, defaults to int.\n\
	-n:\tSort using [threads] worker threads\n\
	-r:\tTime the sort, has no other arguments\n\
	-help:\tPrints this dialogue.  Doesn't sort.\n\n\
If no arguements are specified:\n\
	[listsize] required, number of elements to have in\n\
		randomly generated array to sort\n",
		callingName);
	exit(EXIT_FAILURE);
}

/* Parse the arguements of program parameters into a mergeParas */
signed char merge_parseArgs(mergeParas *args, int argc, char *argv[]) {
	/* Requires at least one argument in any case */
	if(argc < 2)
		merge_helpExit(argv[0]);

	unsigned int numRands = merge_sizeLimit,
		counter = 1;
	char typed = 0, 
		timed = 0,
		threaded = 0,
		counted = 0;

	while(counter < argc) {
		if(argv[counter][0] == '-') {
			switch(argv[counter][1]) {
				/* Set the type flag, if it is already set bad formatting */
				case 't':
					if(typed++) {
						fprintf(stderr, "Can't assign multiple types\n");
						return -1;
					}
					if(++counter == argc) {
						fprintf(stderr, "Type arguement provided no type at end of input\n");
						return -1;
					}
					switch(argv[counter][0]) {
						case '0':
							args->dataType = MINT;
							break;
						case '1':
							args->dataType = MLONG;
							break;
						case '2':
							args->dataType = MFLOAT;
							break;
						case '3':
							args->dataType = MDOUBLE;
							break;
						default:
							fprintf(stderr, "Invalid type declarator.  Use:\n \
	0 for int, 1 for long, 3 for float, or 4 for double\n");
							return -1;
					}
					break;
				
				case 'r':
					if(timed++) {
						fprintf(stderr, "Repeated declarations of timed\n");
						return -1;
					}
					break;
				/* We are to specify the number of threads to run.  Interestingly, GCC
				 * won't compile case statements if they declare variables and are not
				 * wrapped in braces. */
				case 'n': {
					if(threaded++) {
						fprintf(stderr, "Can't specifiy number of threads multiple times\n");
						return -1;
					}
					if(++counter == argc) {
						fprintf(stderr, "Number threads provided no number to use at end of input\n");
						return -1;
					}
					unsigned short numThreads = parseUnsignedShort(argv[counter]);
					/* This happens if you use bad formatting */
					if(numThreads <= 0) {
						fprintf(stderr, "Bad formatting of number of threads\n");
						return -1;
					}
					args->numThreads = numThreads;
					} break;

				/* h case means we probably have help, but even
				 * if we have formatting error, we exit the same way */
				case 'h':
					merge_helpExit(argv[0]);
					break;

				/* Default case means we have bad formatting, while we
				 * could do the help case, we may not want to exit in
				 * the general case */
				default:
					fprintf(stderr, "Bad formatting of flag argument #%d: %s\n",
						counter, argv[counter]);
					return -1;
			}

		/* Assume we have a random array generator value */
		} else {
			if(counted++) {
				fprintf(stderr, "Can't give multiple sizes of random numbers.\n");
				return -1;
			}
			numRands = parseUnsignedInt(argv[counter]);
			if(numRands == 0) {
				fprintf(stderr, "Formatting error on number of random numbers \
					to generate.  Try again.\n");
				return -1;
			}
		}
		counter++;
	}

	args->length = numRands;
	
	switch(args->dataType) {
		case MINT:
			args->array = randomInts(numRands);
			break;
		case MLONG:
			args->array = randomLongs(numRands);
			break;
		case MFLOAT:
			args->array = randomFloats(numRands);
			break;
		case MDOUBLE:
			args->array = randomDoubles(numRands);
			break;	
		default:
			fprintf(stderr, "Invalid type argument.  \
				This shouldn't be able to happen.\n");
			return -1;
		}
	return timed;
}
