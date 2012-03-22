#include "merge.h"

void * merge(mergeParas *args) {

	//TODO : IMPLEMENT SORT

}

int main(int argc, char *argv[]) {
	mergeParas args;

	/* If our arguements parsing fails, we print help */
	if(parseArgs(&args, argc, argv))
		merge_helpExit(argv[0]);

	double start = MPI_Wtime();

	void *merged = merge(&args);

	printf("Merge took %f seconds\n", MPI_Wtime() - start);

	free(args.array);
	free(merged);

	exit(EXIT_SUCCESS);
}
