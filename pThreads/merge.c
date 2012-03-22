#include "merge.h"

/* If the user doesn't specify, it is serial on
 * an external thread */
unsigned short merge_numThreads = 1;

/* Hard limit on number of threads in system */
const unsigned short merge_maxThreads = 1024;

unsigned short merge_getNumThreads() {
	return merge_numThreads;
}

void merge_SetNumThreads(unsigned short numThreads) {
	merge_numThreads = numThreads;
}

void merge_serialSort(void * start, unsigned long length, unsigned char type) {

	//@TODO : implement serial sorting algorithm for sub arrays, bucket sort?

}

/* Threadable function to merge sort a data range,
 * Takes a pt_mergeData cast into void* */
void merge_worker(void* args) {

	// @TODO : implement worker algorithm
	
	pthread_exit();
}

/* Merge function, takes the start address of an
 * array to sort, the length of the array, and the size
 * of the integer or float contents of each index to be
 * compared (in bytes).  Can sort characters, but will do
 * so by ascii value.  It will recursively call itself until
 * out of threads to generate */
void merge(mergeParas *args) {
	unsigned short counter;

	// @TODO : implement merge algorithm
	
	unsigned long numPerThread = length / numThreads,
		remainder = length % numThreads;

	pthread_t threads[2];
	mergeParas args[2];

	for(counter = 0; counter < 2; counter++) {
		args[counter
		args[counter].length = numPerThread + (counter / remainder);
		if(pthread_create(&threads[counter], NULL, &merge_worker, (void*) &args[counter])) {
			fprintf(stderr, "Error in worker thread %d\n", counter);
			exit(EXIT_FAILURE);
		}
	}

	/* Merge worker threads back when they finish merging */
	for(counter = 0; counter < numThreads; counter++) {
		if(pthread_join(threads[counter], NULL)) {
			fprintf(stderr, "Error joining worker thread %d\n", counter);
			exit(EXIT_FAILURE);
		}
	}
}

int main(int argc, char *argv[]) {
	mergeParas args;

	/* If our arguements parsing fails, we print help */
	if(parseArgs(&args, argc, argv))
		merge_helpExit(argv[0]);

	float start = time(NULL);

	void *merged = merge(&args);

	printf("Merge took %f seconds\n", time(NULL) - start);

	free(args.array);
	free(merged);

	exit(EXIT_SUCCESS);
}
