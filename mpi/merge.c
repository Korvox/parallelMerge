/* MPI Distributed Merging
 * @author Matthew Scheirer
 * @license GPL v3 */

#include "merge.h"

void * merge(mergeParas *args) {
	int id, nprocs;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);

	//@todo IMPLEMENT SORT


	MPI_Finalize();

	return array;
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
