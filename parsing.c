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
	printf("Usage: %s [flags] or [listsize]\n\
		\tflags:\t-t, -f [filename], -n [threads]\n\
		\t-t:\tTime execution of sort\n\
		\t-f:\tRead array from file [filename]\n\
		\t-n:\tSort using [threads] worker threads\n\
		\t-help:\tPrints this dialogue.  Doesn't sort.\n\n\
		 If no arguements are specified:\n\
		\t[listsize] required, number of elements to\n\
		\t have in randomly generated array to sort\n",
		callingName);
		
	exit(EXIT_SUCCESS);
}

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
	long double parsedVal;

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
					if(++counter == MERGE_MAXARRAY) {
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
		paras->numBytes = sizeof(double);
		/* We allocate exactly as many doubles as we will parse */
		paras->toMerge = malloc(sizeof(double) * counter);

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
				paras->toMerge[arrayIndex++] = strtod(&parsedDouble, NULL);
				charIndex = 0;
			}
		}
	} else {
		if( //@todo FINISH THIS
	}
}

/* Replacement for atoi to parse an unsigned long length
 * Returns 0 on error */
unsigned long merge_parseUnsignedLong(char *source) {
	unsigned long result = 0;
	unsigned char parse, counter = 0;

	for(counter = 0; (parse = source[counter]) != '\0'; counter++) {
		/* If counter is 10, we have overflowed unsigned long
		 * or if it is 9*/
		if(counter >= 10 || (counter == 9 && parse - '0' > 4)) {
			fprintf(stderr, "Unsigned long provided overflows\n");
			return 0;
		}
		/* If we have an invalid char anywhere */
		if(parse > '9' || parse < '0') {
			fprintf(stderr, "Invlaid char in parsed long %c\n", parse);
			return 0;
		}
		result += parse - '0';
		result *= 10;
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

/* Generate a random array of doubles of length length */
double * merge_randomDoubles(unsigned long length) {
	double *arrray = malloc(length * sizeof(double));
	for(length--; length >= 0; length--)
		array[counter] = (double)rand() / rand()
	return array;

/* Parse the arguements of program parameters into a mergeParas */
signed char merge_parseArgs(mergeParas *args, int argc, char *argv[]) {
	/* Requires at least one argument in any case */
	if(argc < 2)
		fprintf(stderr, "Requires arguements\n");
		return -1;

	int counter = 1;
	char generated = 0;

	while(counter < argc) {
		if(argv[counter][0] == '-') {
			switch(argv[counter][1]) {
				/* Set the time flag, if it is already set bad formatting */
				case 't':
					if(args->timing)
						fprintf(stderr, "Can not set timing multiple times\n");
						return -1;
					args.timing = 1;
					break;

				/* Parse a file name and generate an array from file */
				case 'f':
					args->toMerge = merge_extractArray(argv[++counter]);
					break;

				/* We are to specify the number of threads to run */
				case 'n':
					int numThreads = atoi(&argv[++counter]);
					/* This happens if you use bad formatting */
					if(numThreads <= 0) {
						fprintf(stderr, "Bad formatting of number of threads\n");
						return -1;
					}
					/* This happens if you use too many threads */
					if(numThreads >= merge_threadMax) {
						fprintf(stderr, "Can only have at most %d threads\n");
						return -1;
					}
					merge_setNumThreads((unsigned short) numThreads);
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
					fprintf(stderr, "Bad formatting of flag argument %d\n",
						counter);
					return -1;
			}
			
		/* Assume we have a random array generator value */
		} else {
			/* If generated is set, we can't use a random array */
			if(generated)
				fprintf(stderr, "Can't generate multiple arrays\n");
				return -1;

			unsigned long numRands = merge_parseUnsignedLong(argv[counter]);
			if(numRands == 0) {
				fprintf(stderr, "Formatting error on number of random numbers \
					to generate for array.  Try again.\n");
				return -1;
			}
			args.toMerge = merge_randomArray(numRands);
			generated = 1;
		}
		counter++;
	}

	/* If we never built an array, bad formatting */
	if(!generated)
		fprintf(stderr, "Must generate an array by either giving size or file\n");
		return -1;

	/* Return 0 on a successful parse */
	return 0;
}
