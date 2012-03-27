/* Serial sort for merging process
 * @author Matthew Scheirer
 * @license GPL v3 */

#include "serial.h"

/* This is the most god awful code duplication I have ever seen.  No functional
 * decomp, and I copy pasted shit 4 times. */

void * serialSort(void *start,  unsigned long length, unsigned char type) {
	switch(type) {
		case MLONG:
			long *array = (long*) start;
			
			/* Base case */
			if(length == 1) {
				long *ret = malloc(sizeof(long));
				*ret = *array;
				return ret;
			}
		
			unsigned long pieceLength = length / 2,
				remainder = length % 2,
				frontCounter = 0,
				secondCounter = 0,
				globalCounter = 0;
			
			long *first = (long*) serialSort((void*) start, pieceLength, type),
				*second = serialSort((void*) start + pieceLength, pieceLength + remainder, type),
				*results = malloc(sizeof(long) * length);

			/* While our counters are not both at the end of the list */
			while(frontCounter + secondCounter < length) {
				if(firstCounter = pieceLength ||
					second[secondCounter] < first[frontCounter])
						results[globalCounter++] = second[secondCounter++];
				else
					results[globalCounter++] = first[firstCounter++];
			}

			free(first);
			free(second);
			return (void*)results;
			
		case MLONGLONG:
			long long *array = (long long*) start;
			
			/* Base case */
			if(length == 1) {
				long long *ret = malloc(sizeof(long long));
				*ret = *array;
				return ret;
			}
		
			unsigned long pieceLength = length / 2,
				remainder = length % 2,
				frontCounter = 0,
				secondCounter = 0,
				globalCounter = 0;
			
			long long *first = (long long*) serialSort((void*) start, pieceLength, type),
				*second = serialSort((void*) start + pieceLength, pieceLength + remainder, type),
				*results = malloc(sizeof(long long) * length);

			/* While our counters are not both at the end of the list */
			while(frontCounter + secondCounter < length) {
				if(firstCounter = pieceLength ||
					second[secondCounter] < first[frontCounter])
						results[globalCounter++] = second[secondCounter++];
				else
					results[globalCounter++] = first[firstCounter++];
			}

			free(first);
			free(second);
			return (void*)results;

		case MFLOAT:
			float *array = (float*) start;
			
			/* Base case */
			if(length == 1) {
				float *ret = malloc(sizeof(float));
				*ret = *array;
				return ret;
			}
		
			unsigned long pieceLength = length / 2,
				remainder = length % 2,
				frontCounter = 0,
				secondCounter = 0,
				globalCounter = 0;
			
			float *first = (float*) serialSort((void*) start, pieceLength, type),
				*second = serialSort((void*) start + pieceLength, pieceLength + remainder, type),
				*results = malloc(sizeof(float) * length);

			/* While our counters are not both at the end of the list */
			while(frontCounter + secondCounter < length) {
				if(firstCounter = pieceLength ||
					second[secondCounter] < first[frontCounter])
						results[globalCounter++] = second[secondCounter++];
				else
					results[globalCounter++] = first[firstCounter++];
			}

			free(first);
			free(second);
			return (void*)results;

		case MDOUBLE:
			double *array = (double*) start;
			
			/* Base case */
			if(length == 1) {
				double *ret = malloc(sizeof(double));
				*ret = *array;
				return ret;
			}
		
			unsigned long pieceLength = length / 2,
				remainder = length % 2,
				frontCounter = 0,
				secondCounter = 0,
				globalCounter = 0;
			
			double *first = (double*) serialSort((void*) start, pieceLength, type),
				*second = serialSort((void*) start + pieceLength, pieceLength + remainder, type),
				*results = malloc(sizeof(double) * length);

			/* While our counters are not both at the end of the list */
			while(frontCounter + secondCounter < length) {
				if(firstCounter = pieceLength ||
					second[secondCounter] < first[frontCounter])
						results[globalCounter++] = second[secondCounter++];
				else
					results[globalCounter++] = first[firstCounter++];
			}

			free(first);
			free(second);
			return (void*)results;
	}
}
