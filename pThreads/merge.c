#include "pt_merge.h"

/* If the user doesn't specify, it is serial on
 * an external thread */
unsigned short ptMerge_numThreads = 1;

/* Hard limit on number of threads in system */
const unsigned short ptMerge_maxThreads = 1024;

unsigned short ptMerge_getNumThreads() {
	return ptMerge_numThreads;
}

void ptMerge_SetNumThreads(unsigned short numThreads) {
	ptMerge_numThreads = numThreads;
}

/* Threadable function to merge sort a data range,
 * Takes a pt_mergeData cast into void* */
void ptMerge_worker(void* args) {













	
	pthread_exit();
}

/* Merge function, takes the start address of an
 * array to sort, the length of the array, and the size
 * of the integer or float contents of each index to be
 * compared (in bytes).  Can sort characters, but will do
 * so by ascii value.  It will recursively call itself until
 * out of threads to generate */
void ptMerge(void *args) {
	unsigned short counter;











	unsigned long numPerThread = length / numThreads,
		remainder = length % numThreads;

	pthread_t threads[2];
	ptMerge_paras args[2];

	for(counter = 0; counter < 2; counter++) {
		args[counter
		args[counter].length = numPerThread + (counter / remainder);
		if(pthread_create(&threads[counter], NULL, &ptMerge_worker, (void*) &args[counter])) {
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
	ptMerge_paras args;

	/* If our arguements parsing fails, we print help */
	if(parseArgs(&args, argc, argv)
		ptMerge_helpExit();

	float start;

	/* If we are to do timings */
	if(args.timing > 0)
		start = time(NULL);

	/* We execute our merge on our array, with a fixed size,
	 * and the size of the integral buckets in the array */
	void *merged = ptMerge(args.toMerge, args.numIndexes, args.numBytes);

	if(args.timing > 0)
		printf("Merge took %f seconds\n", time(NULL) - start);

	free(args.toMerge);
	free(merged);

	exit(EXIT_SUCCESS);
}
