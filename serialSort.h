/* Serial sort for merging process
 * @author Matthew Scheirer
 * @license GPL v3 */

#ifndef _SERIALSORTER_
#define _SERIALSORTER_

//#include "../parsing.h"

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

void * serialSort(void*, unsigned long, unsigned char);

#endif
