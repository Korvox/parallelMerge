/* Testing the arguments parser
 * @author Matthew Scheirer
 * @license GPL v3 */
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "general/general.h"

void printArgs(mergeParas *args) {
	printf("Args: DataType: %hu Length: %u Threads: %u\n",
		args->dataType, args->length, args->numThreads);
}

int main(int argc, char *argv[]) {
	mergeParas parameters;
	
	switch(merge_parseArgs(&parameters, argc, argv)) {
		case 0:
			printf("Parsing successful and got told to time\n");
			printArgs(&parameters);
			break;

		case 1:
			printf("Parsing successful and got told not to time\n");
			printArgs(&parameters);
			break;

		default:
			printf("Error occured in parsing\n");
	}
	exit(EXIT_SUCCESS);
}
