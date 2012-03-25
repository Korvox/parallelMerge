/* MPI Distributed Merging
 * @author Matthew Scheirer
 * @license GPL v3 */

#include "merge.h"

/* Hard limit on number of threads in system
 * NOTE: maximum number of cluster compute nodes
 * in lab is 8 * 8 + 16 = 80 */
const unsigned short merge_maxThreads = 128;

void * merge(mergeParas *args) {
	int id;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	/* I guess we ignore the nprocs arg? */
	MPI_Comm_size(MPI_COMM_WORLD, &args->numThreads);

	//@todo IMPLEMENT SORT

	MPI_Finalize();
	return array;
}
