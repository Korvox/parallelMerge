/* Parallel Merge Parsing
 * @author Matthew Scheirer
 * @license GPL v3 */

#include "parsing/parsing.h"
#include "serialSort/serialSort.h"

/* -------------------WARNING------------------
 * This must be compiled with an included paralell sorter,
 * or it will fail to build.  And it must be defined before
 * this file is compiled. */

#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
	mergeParas args;

	/* If our arguements parsing fails, we print help */
	if(parseArgs(&args, argc, argv))
		merge_helpExit(argv[0]);

	srand(123456789);
	float start = time(NULL);

	void *merged = merge(&args, &serialSort);

	printf("Merge took %f seconds\n", time(NULL) - start);
	free(args.array);
	free(merged);

	return 0;
}
