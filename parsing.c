/* Parallel Merge Parsing
 * @author Matthew Scheirer
 * @license GPL v3 */

#include "parsing.h"

/* This is an error exit condition if any file operations fail */
void merge_fileErrorExit(FILE *toClose) {
	fclose(toClose);
	if(errno)
		fprintf(stderr, "Errno set: %s\n", strerror(errno));
	else
		fprintf(stderr, "Given file improperly formatted:\n\
			\t1. Must contain only numbers, can have decimal places and signs\n\
			\t2. Numbers can be followed by tab, space, or new line\n\
			\t3. File must end with EOF\n");
	exit(EXIT_SUCCESS);
}

/* This error prints the usage of merge */
void merge_helpExit(char *callingName) {
	printf("Usage: %s [flags] [listsize]\n\
		\tflags:\t-t [type #], -f [filename], -n [threads],\n\
		\t-t:\tType of elements.  If not specified, defaults to long int.\n\
		\t-f:\tRead array from file [filename]\n\
		\t-n:\tSort using [threads] worker threads\n\
		\t-help:\tPrints this dialogue.  Doesn't sort.\n\n\
		 If no arguements are specified:\n\
		\t[listsize] required, number of elements to\n\
		\t have in randomly generated array to sort\n",
		callingName);
	exit(EXIT_SUCCESS);
}

//@todo BREAK THIS UP into long, long long, float, and double file parsers. \
	Assume correctness, if anything is wrong just file error exit.

/* Given a file name to open, attempt to parse it into an array */
void merge_extractArray(char *fileName, mergeParas *paras) {
	FILE *data = fopen(filename, 'r');

	/* If file failed to open, exit with file error */
	if(data == NULL)
		merge_fileErrorExit(data);

	unsigned char parse,
		floating = 0,
		decimal = 0;
		longestDigits = 0,
		numDigits = 0,
		checkDigit = 0;
	unsigned long counter = 0;

	/* We need to search for decimal points to determine if file values are
	 * floating or not.  Also, check for file integrity, so we can directly parse
	 * numbers in the event we don't have invalid chars.  We don't allow e or pi.*/
	while((parse = fgetc(data)) != EOF) {
		switch(parse) {
			/* If parse is a sign */
			case '+':
			case '-':
				if(numDigits > 0) {
					fprintf(stderr, "Numeric sign miday in a number\n");
					merge_fileErrorExit(data);
				}
				checkDigit = 1;
				break;

			/* If parse is a decimal point */
			case '.':
				if(decimal == 1) {
					fprintf(stderr, "Multiple decimal points in single number\n");
					merge_fileErrorExit(data);
				}
				floating = decimal = 1;
				break;

			/* If parse is a spacing char */
			case ' ':
			case '\t':
			case '\n':
				/* numdigits > 0 allows trailing whitespace to not increment counter */
				if(numDigits > 0) {
					if(++counter == merge_maxArray) {
						fprintf(stderr, "Too many numbers to parse in file\n");
						merge_fileErrorExit(data);
					}

					if(numDigits > longestDigits)
						longestDigits = numDigits;
					numDigits = 0;
				}
				break;

			/* Try to parse a digit, or if an invalid char escape */
			default:
				if(parse < '0' || parse > '9') {
					fprintf(stderr, "Invalid character in file: %c", parse);
					merge_fileErrorExit(data);
				}
				numDigits++;
				break;
		}
	}

	/* We reset the file pointer back to the start */
	rewind(data);

	/* We either process the file as doubles or ints for the array */
	if(floating) {
		/* Set the paras size of elements */
		paras->dataType = MDOUBLE;
		/* We allocate exactly as many doubles as we will parse */
		double *data = malloc(sizeof(double) * counter);

		/* We can have a char buffer for reading in exactly as
		 * large as the longest double we will parse*/
		unsigned char[longestDigits + 2] parsedDouble,
			charIndex = 0;
		unsigned long arrayIndex = 0;
		
		while((parse = fgetc(data)) != EOF) {
			/* This is why we checked file integrity, makes this part ezpz */
			if(parse != 9 && parse != 10 && parse != 32)
				parsedDouble[charIndex++] = parse;
			/* We write the double into the array given we parsed something
			 * otherwise we are just skipping trailing whitespace chars */
			else if(charIndex > 0) {
				parsedDouble[charIndex] = '\0';
				data[arrayIndex++] = strtod(&parsedDouble, NULL);
				charIndex = 0;
			}

		paras->array = data;
		}
	} else {
		/* Else parse longs or long longs */
		if( //@todo FINISH THIS
	}
}

/* Replacement for atoi to parse an unsigned long length
 * Returns 0 on error */
unsigned long merge_parseUnsignedLong(char *source) {
	unsigned long result = 0;
	unsigned char parse,
		counter = 0;

	while(parse = source[counter]) != '\0') {
		/* If we have an invalid char anywhere */
		if(parse < '0' || parse > '9') {
			fprintf(stderr, "Invlaid char in parsed long %c\n", parse);
			return 0;
		}

		/* Covert parse into its true digit value */
		parse -= '0';

		if(++counter >= 10 && result * 10 + parse > ULONG_MAX) {
			fprintf(stderr, "Given input %s overflows unsigned long %lu\n",
				source, ULONG_MAX);
			return 0;
		}	
		
		result *= 10;
		result += parse;
	}
	return result;
}

/* Generate a random array of longs of length length*/
long * merge_randomLongs(unsigned long length) {
	long *array = malloc(length * sizeof(long));
	for(length--; length >= 0; length--)
		array[counter] = rand();
	return array;
}

/* Generate a random array of floats of length length */
float * merge_randomfloats(unsigned long length) {
	float *arrray = malloc(length * sizeof(float));
	for(length--; length >= 0; length--)
		array[counter] = (float)rand() / rand()
	return array;
}

/* Generate a random array of doubles of length length */
double * merge_randomDoubles(unsigned long length) {
	double *arrray = malloc(length * sizeof(double));
	for(length--; length >= 0; length--)
		array[counter] = (double)rand() / rand()
	return array;
}

//@todo Change parsing logic - require a type for files, default to \
	long for non-files, and parse files after parsing other args

/* Parse the arguements of program parameters into a mergeParas */
signed char merge_parseArgs(mergeParas *args, int argc, char *argv[]) {
	/* Requires at least one argument in any case */
	if(argc < 2)
		fprintf(stderr, "Requires arguements\n");
		return -1;

	int counter = 1;
	unsigned char typed = 0,
		*filename = NULL;
	unsigned long numRands = 0;

	while(counter < argc) {
		if(argv[counter][0] == '-') {
			switch(argv[counter][1]) {
				/* Set the time flag, if it is already set bad formatting */
				case 't':
					if(typed++) {
						fprintf(stderr, "Can't assign multiple types\n");
						return -1;
					}
					switch(argv[++counter][0]) {
						case '0':
							args->dataType = MLONG;
							break;
						case '1':
							args->dataType = MLONGLONG;
							break;
						case '2':
							args->dataType = MFLOAT;
							break;
						case '3':
							args->dataType = MDOUBLE;
							break;
						default:
							fprintf(stderr, "Invalid type declarator.  Use:\n \
								\t0 for long, 1 for long long, or 2 for double\n");
							return -1;
					}
					break;
					
				/* Parse a file name and generate an array from file */
				case 'f':
					if(filename != NULL || numRands != 0) {
						fprintf(stderr, "Can't generate multiple arrays\n");
						return -1;
					}
					filename = argv[++counter];
					break;
					
				/* We are to specify the number of threads to run */
				case 'n':
					unsigned long numThreads = merge_parseUnsignedLong(argv[++counter]);
					/* This happens if you use bad formatting */
					if(numThreads <= 0) {
						fprintf(stderr, "Bad formatting of number of threads\n");
						return -1;
					}
					/* This happens if you use too many threads
					 * @todo CANT DO THIS, THREAD MAX IS IN MERGE.C
					if(numThreads >= merge_maxThreads) {
						fprintf(stderr, "Can only have at most %d threads\n", MERGE_MAXTHREADS);
						return -1;
					} */
					args->numThreads = numThreads;
					break;

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
			if(filename != NULL || numRands != 0) {
				fprintf(stderr, "Can't generate multiple arrays\n");
				return -1;
			}
			
			numRands = merge_parseUnsignedLong(argv[++counter]);
			
			if(numRands <= 0) {
				fprintf(stderr, "Formatting error on number of random numbers \
					to generate.  Try again.\n");
				return -1;
			}
		}
		counter++;
	}

	/* If we have a valid filename */
	if(filename != NULL) {
		switch(args->dataType) {
			case MLONG:
				args->array = merge_extractLongArray(filename);
				break;
			case MLONGLONG:
				args->array = merge_extractLongLongArray(filename);
				break;
			case MFLOAT:
				args->array = merge_extractFloatArray(filename);
				break;
			case MDOUBLE:
				args->array = merge_extractDoubleArray(filename);
				break;
			default:
				fprintf(stderr, "This error should never happen, bigger problems if it did.\n");
				return -1;
		}
	/* Else check if we parsed for random array */
	} else if(numRands != 0) {
		switch(args->dataType) {
			case MLONG:
				args->array = merge_randomLongs(numRands);
				break;
			case MLONGLONG:
				// @todo IMPLEMENT RANDOM LONG LONG ARRAYS
				fprintf(stderr, "Can't generate random long long array yet.\n");
				return -1;
			case MFLOAT:
				args->array = merge_randomFloats(numRands);
				break;
			case MDOUBLE:
				args->array = merge_randomDoubles(numRands);
				break;	
			default:
				fprintf(stderr, "This error should never happen, bigger problems if it did.\n");
				return -1;
		}	
	} else {
		/* If we never built an array, bad formatting */
		fprintf(stderr, "Must generate an array by either giving size or file\n");
		return -1;
	}
	/* Return 0 on a successful parse */
	return 0;
}
