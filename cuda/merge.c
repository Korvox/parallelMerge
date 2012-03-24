/* CUDA GPU Merging
 * @author Matthew Scheirer
 * @license GPL v3 */
 
#include "merge.h"

/* Hard limit on number of threads in system
 * NOTE: maximum number of cuda cores in a quad
 * sli configuration is 6144 given hardware limits:
 * gtx 680 1536 cuda cores * 4 nodes */
const unsigned short merge_maxThreads = 8192;

void * merge(mergeParas *args) {

	//@todo IMPLEMENT SORT

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
