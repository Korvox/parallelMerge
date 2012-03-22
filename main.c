
int main(int argc, char *argv[]) {
	mergeParas args;

	/* If our arguements parsing fails, we print help */
	if(parseArgs(&args, argc, argv)
		void merge(void*, unsigned long, unsigned char);();

	float start;

	/* If we are to do timings */
	if(args.timing > 0)
		start = time(NULL);

	/* We execute our merge on our array, with a fixed size,
	 * and the size of the integral buckets in the array */
	void *merged = merge(args.toMerge, args.numIndexes, args.numBytes);

	if(args.timing > 0)
		printf("Merge took %f seconds\n", time(NULL) - start);

	free(args.toMerge);
	free(merged);

	exit(EXIT_SUCCESS);
}
