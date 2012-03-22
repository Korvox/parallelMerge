/* MPI Distributed Merging
 * @author Matthew Scheirer
 * @license GPL v3 */

#ifndef _MPIMERGE_
#define _MPIMERGE_

#include "../parsing.h"
#include "../serialSort.h"
#include <mpi.h>

void * merge(mergeParas*);

#endif
