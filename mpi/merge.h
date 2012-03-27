/* MPI Distributed Merging
 * @author Matthew Scheirer
 * @license GPL v3 */

#ifndef _MPIMERGE_
#define _MPIMERGE_

#include <mpi.h>

//@todo again, we have massive duplication of these declarations

/* These macros are used to denote the type of elements in array */
#ifndef MLONG
#define MLONG 0
#endif
#ifndef MLONGLONG
#define MLONGLONG 1
#endif
#ifndef MFLOAT
#DEFINE MFLOAT 2
#endif
#ifndef MDOUBLE
#define MDOUBLE 3
#endif

/* Structure for the arguments processing */
#ifndef MERGEPARAS
#define MERGEPARAS
typedef struct {
	unsigned char dataType = 0;
	unsigned long length,
		numThreads = 1;
	void *array;
} mergeParas;
#endif

//@todo Should we split up the args into component parameters \
	so we don't have to redefine mergeParas everywhere?

void * merge(mergeParas*);

#endif
