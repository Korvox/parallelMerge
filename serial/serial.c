/* Serial sort for merging process
 * @author Matthew Scheirer
 * @license GPL v3 */

#include "serial.h"

/* This is the most god awful code duplication I have ever seen.  No functional
 * decomp, and I copy pasted shit 4 times. */

void * serialSort(void *start,  unsigned long length, unsigned char type) {
	//printf("%lu %hu\n", length, type);
	switch(type) {
		case MINT: {
			int *array = (int*) start,
				*results;
			
			/* Base case */
			if(length == 1) {
				results = malloc(sizeof(int));
				*results = *array;
			} else {
				unsigned long firstLength = length / 2,
					secondLength = firstLength + length % 2;
			
				int *first = (int*) serialSort((void*) array, firstLength, type),
					*second = serialSort((void*) &array[firstLength],
								secondLength, type);

				results = malloc(sizeof(int) * length);
				unsigned long firstCounter = 0,
					secondCounter = 0,
					globalCounter = 0;

				while(globalCounter < length) {
					if(firstCounter == firstLength)
						results[globalCounter++] = second[secondCounter++];
					else if(secondCounter == secondLength)
						results[globalCounter++] = first[firstCounter++];
					else if(first[firstCounter] < second[secondCounter])
						results[globalCounter++] = first[firstCounter++];
					else 
						results[globalCounter++] = second[secondCounter++];
				}
				free(first);
				free(second);
			}
			return (void*) results;
		}
		case MLONG: {
			long *array = (long*) start,
				*results;
			
			/* Base case */
			if(length == 1) {
				results = malloc(sizeof(long));
				*results = *array;
			} else {
				unsigned long firstLength = length / 2,
					secondLength = firstLength + length % 2;
			
				long *first = (long*) serialSort((void*) array, firstLength, type),
					*second = serialSort((void*) &array[firstLength],
								secondLength, type);

				results = malloc(sizeof(long) * length);
				unsigned long firstCounter = 0,
					secondCounter = 0,
					globalCounter = 0;

				while(globalCounter < length) {
					if(firstCounter == firstLength)
						results[globalCounter++] = second[secondCounter++];
					else if(secondCounter == secondLength)
						results[globalCounter++] = first[firstCounter++];
					else if(first[firstCounter] < second[secondCounter])
						results[globalCounter++] = first[firstCounter++];
					else 
						results[globalCounter++] = second[secondCounter++];
				}
				free(first);
				free(second);
			}
			return (void*) results;
		}	
		case MFLOAT: {
			float *array = (float*) start,
				*results;
			
			/* Base case */
			if(length == 1) {
				results = malloc(sizeof(float));
				*results = *array;
			} else {
				unsigned long firstLength = length / 2,
					secondLength = firstLength + length % 2;
			
				float *first = (float*) serialSort((void*) array, firstLength, type),
					*second = serialSort((void*) &array[firstLength],
								secondLength, type);

				results = malloc(sizeof(float) * length);
				unsigned long firstCounter = 0,
					secondCounter = 0,
					globalCounter = 0;

				while(globalCounter < length) {
					if(firstCounter == firstLength)
						results[globalCounter++] = second[secondCounter++];
					else if(secondCounter == secondLength)
						results[globalCounter++] = first[firstCounter++];
					else if(first[firstCounter] < second[secondCounter])
						results[globalCounter++] = first[firstCounter++];
					else 
						results[globalCounter++] = second[secondCounter++];
				}
				free(first);
				free(second);
			}
			return (void*) results;
		}
		case MDOUBLE: {
			double *array = (double*) start,
				*results;
			
			/* Base case */
			if(length == 1) {
				results = malloc(sizeof(double));
				*results = *array;
			} else {
				unsigned long firstLength = length / 2,
					secondLength = firstLength + length % 2;
			
				double *first = (double*) serialSort((void*) array, firstLength, type),
					*second = serialSort((void*) &array[firstLength],
								secondLength, type);

				results = malloc(sizeof(double) * length);
				unsigned long firstCounter = 0,
					secondCounter = 0,
					globalCounter = 0;

				while(globalCounter < length) {
					if(firstCounter == firstLength)
						results[globalCounter++] = second[secondCounter++];
					else if(secondCounter == secondLength)
						results[globalCounter++] = first[firstCounter++];
					else if(first[firstCounter] < second[secondCounter])
						results[globalCounter++] = first[firstCounter++];
					else 
						results[globalCounter++] = second[secondCounter++];
				}
				free(first);
				free(second);
			}
			return (void*) results;
		}
		/* If the type is invalid return null */
		default:
			fprintf(stderr, "Invalid type passed to merge sort %hu", type);
			return NULL;
	}
}
