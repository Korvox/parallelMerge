/* Serial sort for merging process
 * @author Matthew Scheirer
 * @license GPL v3 */

#ifndef _SERIALSORTER_
#define _SERIALSORTER_

#include <stdio.h>
#include <stdlib.h>

/* These macros are used to denote the type of elements in array */
#ifndef MINT
#define MINT 0
#endif
#ifndef MLONG
#define MLONG 1
#endif
#ifndef MFLOAT
#define MFLOAT 2
#endif
#ifndef MDOUBLE
#define MDOUBLE 3
#endif

void * serialSort(void*, unsigned long, unsigned char);

#endif
