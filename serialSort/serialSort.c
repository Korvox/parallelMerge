/* Serial sort for merging process
 * @author Matthew Scheirer
 * @license GPL v3 */

#include "serialSort.h"

void * serialSort(void *start,  unsigned long length, unsigned char type) {
	/* Merge base case */
	if(length == 1)
		return start;

	/* Split collection and recurse */

	if(type == MLONG) {
		long *array = (long*) start;
		
		unsigned long pieceLength = length / 2,
			remainder = length % 2;
		serialSort((void*) start, 

	
	
}
