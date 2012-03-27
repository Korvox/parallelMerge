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
	exit(EXIT_FAILURE);
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
	exit(EXIT_FAILURE);
}

long * merge_extractLongArray(char *filename) {
	FILE *data = fopen(filename, "r");

	/* If file failed to open, exit with file error */
	if(data == NULL)
		merge_fileErrorExit(data);

	unsigned char parse,
		numDigits = 0,
		sign = 0;
	unsigned long counter = 0,
		length = 127;
	long *array = malloc(sizeof(long) * length),
		parsedVal = 0;

	while((parse = fgetc(data)) != EOF) {
		switch(parse) {
			/* If parse is a sign */
			case '+':
			case '-':
				if(numDigits > 0) {
					fprintf(stderr, "Numeric sign midway in a number\n");
					merge_fileErrorExit(data);
				}
				if(sign != 0) {
					fprintf(stderr, "Can only have one sign per number\n");
					merge_fileErrorExit(data);
				}
				sign = parse;
				break;
			/* If parse is a spacing char */
			case ' ':
			case '\t':
			case '\n':
				/* numdigits > 0 allows trailing whitespace to not increment counter */
				if(numDigits > 0) {
					if(++counter == MERGE_MAXARRAY) {
						fprintf(stderr, "Too many numbers to parse in file\n");
						merge_fileErrorExit(data);
					}
					/* Dynamic memory resizer */
					if(counter == length) {
						if(length << 1 > ULONG_MAX) {
							fprintf(stderr,
								"Attempted to resize array longer than ulong max %lu\n",
								ULONG_MAX);
							merge_fileErrorExit(data);
						}
						length = length << 1;
						realloc(array, length * sizeof(long));
					}
					numDigits = parsedVal = sign = 0;
				}
				break;
			/* Try to parse a digit, or if an invalid char escape */
			default:
				if(parse < '0' || parse > '9') {
					fprintf(stderr, "Invalid character in file: %c", parse);
					merge_fileErrorExit(data);
				}
				
				parse -= '0';
				
				if(numDigits++ == 0) {
					if(parse == 0) {
						fprintf(stderr, "Values in file can not have leading zeroes\n");
						merge_fileErrorExit(data);
					}
					parsedVal = parse;
					if(sign == '-')
						parsedVal *= -1;
				} else {
					if(numDigits >= 10 && parsedVal * 10 + parse > LONG_MAX) {
						fprintf(stderr, "Value in file overflows long %lu\n", LONG_MAX);
						merge_fileErrorExit(data);
					}

					parsedVal *= 10;
					parsedVal += parse;
				}
		}
	}

	/* Resize the array back down to the actual size */
	realloc(array, sizeof(long) * counter);
	return array;
}

long long * merge_extractLongLongArray(char *filename) {
	FILE *data = fopen(filename, "r");

	/* If file failed to open, exit with file error */
	if(data == NULL)
		merge_fileErrorExit(data);

	unsigned char parse,
		numDigits = 0,
		sign = 0;
	unsigned long counter = 0,
		length = 63;
	long long *array = malloc(sizeof(long long) * length),
		parsedVal = 0;

	while((parse = fgetc(data)) != EOF) {
		switch(parse) {
			/* If parse is a sign */
			case '+':
			case '-':
				if(numDigits > 0) {
					fprintf(stderr, "Numeric sign midway in a number\n");
					merge_fileErrorExit(data);
				}
				if(sign != 0) {
					fprintf(stderr, "Can only have one sign per number\n");
					merge_fileErrorExit(data);
				}
				sign = parse;
				break;
			/* If parse is a spacing char */
			case ' ':
			case '\t':
			case '\n':
				/* numdigits > 0 allows trailing whitespace to not increment counter */
				if(numDigits > 0) {
					if(++counter == MERGE_MAXARRAY) {
						fprintf(stderr, "Too many numbers to parse in file\n");
						merge_fileErrorExit(data);
					}
					/* Dynamic memory resizer */
					if(counter == length) {
						if(length << 1 > ULONG_MAX) {
							fprintf(stderr,
								"Attempted to resize array longer than ULONG max %lu\n",
								ULONG_MAX);
							merge_fileErrorExit(data);
						}
						length = length << 1;
						realloc(array, length * sizeof(long long));
					}
					numDigits = parsedVal = sign = 0;
				}
				break;
			/* Try to parse a digit, or if an invalid char escape */
			default:
				if(parse < '0' || parse > '9') {
					fprintf(stderr, "Invalid character in file: %c", parse);
					merge_fileErrorExit(data);
				}
				
				parse -= '0';
				
				if(numDigits++ == 0) {
					if(parse == 0) {
						fprintf(stderr, "Values in file can not have leading zeroes\n");
						merge_fileErrorExit(data);
					}
					parsedVal = parse;
					if(sign == '-')
						parsedVal *= -1;
				} else {
					if(numDigits >= 10 && parsedVal * 10 + parse > LLONG_MAX) {
						fprintf(stderr, "Value in file overflows long %lu\n", LLONG_MAX);
						merge_fileErrorExit(data);
					}
					parsedVal *= 10;
					parsedVal += parse;
				}
		}
	}

	/* Resize the array back down to the actual size */
	realloc(array, sizeof(long long) * counter);
	return array;
}

float * merge_extractFloatArray(char *filename) {
	FILE *data = fopen(filename, "r");

	/* If file failed to open, exit with file error */
	if(data == NULL)
		merge_fileErrorExit(data);

	unsigned char parse,
		sign = 0,
		decimal = 0,
		parsed[255],
		numParsed = 0;
	unsigned long counter = 0,
		length = 63;
	float *array = malloc(sizeof(float) * length);

	while((parse = fgetc(data)) != EOF) {
		switch(parse) {
			/* If parse is a sign */
			case '+':
			case '-':
				if(numParsed > 0) {
					fprintf(stderr, "Numeric sign midway in a number\n");
					merge_fileErrorExit(data);
				}
				if(sign != 0) {
					fprintf(stderr, "Can only have one sign per number\n");
					merge_fileErrorExit(data);
				}
				parsed[numParsed++] = parse;
				break;
			/* If parse is a decimal point */
			case '.':
				if(decimal++ > 0) {
					fprintf(stderr, "Multiple decimal points in single number\n");
					merge_fileErrorExit(data);
				}
				parsed[numParsed++] = parse;
				break;
			/* If parse is a spacing char */
			case ' ':
			case '\t':
			case '\n':
				/* numdigits > 0 allows trailing whitespace to not increment counter */
				if(numParsed > 0) {
					if(counter == MERGE_MAXARRAY) {
						fprintf(stderr, "Too many numbers to parse in file\n");
						merge_fileErrorExit(data);
					}
					/* Dynamic memory resizer */
					if(counter == length) {
						if(length << 1 > ULONG_MAX) {
							fprintf(stderr,
								"Attempted to resize array longer than ULONG max %lu\n",
								ULONG_MAX);
							merge_fileErrorExit(data);
						}
						length = length << 1;
						realloc(array, length * sizeof(float));
					}
					if(numParsed > MPARSEFLOATMAX) {
						fprintf(stderr, "Attempted to parse a float of more than %d chars\n",
							MPARSEFLOATMAX);
						merge_fileErrorExit(data);
					}
					parsed[numParsed] = '\0';
					array[counter++] = strtof((const char *)&parsed, NULL);
					numParsed = sign = decimal = 0;
				}
				break;
			/* Try to parse a digit, or if an invalid char escape */
			default:
				if(parse < '0' || parse > '9') {
					fprintf(stderr, "Invalid character in file: %c", parse);
					merge_fileErrorExit(data);
				}
				if(numParsed > MPARSEFLOATMAX) {
					fprintf(stderr, "Attempted to parse a float of more than %d chars\n",
						MPARSEFLOATMAX);
					merge_fileErrorExit(data);
				}
				parsed[numParsed++] = parse - '0';
		}
	}
}

double * merge_extractDoubleArray(char *filename) {
	FILE *data = fopen(filename, "r");

	/* If file failed to open, exit with file error */
	if(data == NULL)
		merge_fileErrorExit(data);

	unsigned char parse,
		sign = 0,
		decimal = 0,
		parsed[255],
		numParsed = 0;
	unsigned long counter = 0,
		length = 63;
	double *array = malloc(sizeof(double) * length);

	while((parse = fgetc(data)) != EOF) {
		switch(parse) {
			/* If parse is a sign */
			case '+':
			case '-':
				if(numParsed > 0) {
					fprintf(stderr, "Numeric sign midway in a number\n");
					merge_fileErrorExit(data);
				}
				if(sign != 0) {
					fprintf(stderr, "Can only have one sign per number\n");
					merge_fileErrorExit(data);
				}
				parsed[numParsed++] = parse;
				break;
			/* If parse is a decimal point */
			case '.':
				if(decimal++ > 0) {
					fprintf(stderr, "Multiple decimal points in single number\n");
					merge_fileErrorExit(data);
				}
				parsed[numParsed++] = parse;
				break;
			/* If parse is a spacing char */
			case ' ':
			case '\t':
			case '\n':
				/* numdigits > 0 allows trailing whitespace to not increment counter */
				if(numParsed > 0) {
					if(counter == MERGE_MAXARRAY) {
						fprintf(stderr, "Too many numbers to parse in file\n");
						merge_fileErrorExit(data);
					}
					/* Dynamic memory resizer */
					if(counter == length) {
						if(length << 1 > ULONG_MAX) {
							fprintf(stderr,
								"Attempted to resize array longer than ULONG max %lu\n",
								ULONG_MAX);
							merge_fileErrorExit(data);
						}
						length = length << 1;
						realloc(array, length * sizeof(double));
					}
					if(numParsed > MPARSEFLOATMAX) {
						fprintf(stderr, "Attempted to parse a double of more than %d chars\n",
							MPARSEFLOATMAX);
						merge_fileErrorExit(data);
					}
					parsed[numParsed] = '\0';
					array[counter++] = strtod((const char *)&parsed, NULL);
					numParsed = sign = decimal = 0;
				}
				break;
			/* Try to parse a digit, or if an invalid char escape */
			default:
				if(parse < '0' || parse > '9') {
					fprintf(stderr, "Invalid character in file: %c", parse);
					merge_fileErrorExit(data);
				}
				if(numParsed > MPARSEFLOATMAX) {
					fprintf(stderr, "Attempted to parse a double of more than %d chars\n",
						MPARSEFLOATMAX);
					merge_fileErrorExit(data);
				}
				parsed[numParsed++] = parse - '0';
		}
	}
}

/* Replacement for atoi to parse an unsigned long length
 * Returns 0 on error */
unsigned long merge_parseUnsignedLong(char *source) {
	unsigned long result = 0;
	unsigned char parse,
		counter = 0;

	while((parse = source[counter]) != '\0') {
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
	while(length > 0)
		array[--length] = rand();
	return array;
}

/* Generate a random array of long longs of length length*/
long long * merge_randomLongLongs(unsigned long length) {
	long long *array = malloc(length * sizeof(long long));
	while(length > 0)
		array[--length] = rand() * rand();
	return array;
}

/* Generate a random array of floats of length length */
float * merge_randomFloats(unsigned long length) {
	float *array = malloc(length * sizeof(float));
	while(length > 0)
		array[--length] = (float)rand() / rand();
	return array;
}

/* Generate a random array of doubles of length length */
double * merge_randomDoubles(unsigned long length) {
	double *array = malloc(length * sizeof(double));
	while(length > 0)
		array[--length] = (double)rand() / rand();
	return array;
}

/* Parse the arguements of program parameters into a mergeParas */
signed char merge_parseArgs(mergeParas *args, int argc, char *argv[]) {
	/* Requires at least one argument in any case */
	if(argc < 2)
		fprintf(stderr, "Requires arguements\n");
		return -1;

	int counter = 1;
	unsigned char typed = 0;
	char *filename = NULL;
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
					
				/* We are to specify the number of threads to run.  Interestingly, GCC
				 * won't compile case statements if they declare variables and are not
				 * wrapped in braces. */
				case 'n': {
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

	/* If we have a valid filename.  Note, if a dataType isn't specified,
	 * the file is assumed to hold valid longs. */
	if(filename != NULL) {
		switch(args->dataType) {
			/*@ todo convert file parser into seperate methods for each data type
			 * also wtb templates in c, holy shit this duplication is gay */
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
				// @todo IMPLEMENT RANDOM LONG LONG ARRAYS WILL REQUIRE COPY / PASTE OF LEHMER RNG
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
