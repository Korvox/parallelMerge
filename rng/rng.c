/* Inline threadsafe RNG implementation
 * @author Matthew Scheirer
 * @license GPL v3 */
 
#include "rng.h"

const int q = MODULUS / MULTIPLIER,
	r = MODULUS % MULTIPLIER;

/* This inline random function prevents integer overflow */
int lehmerRandom(int seed) {
	seed = MULTIPLIER * (seed % q) - r * (seed / q);
	return seed > 0 ? seed : seed + MODULUS;
}

/* Generate numSeeds seed values, such that there are a total of
 * MODULUS - 1 / numSeeds random numbers between each seed in the rng */
int * generateSeeds(unsigned char numSeeds) {
	int *seeds = malloc(numSeeds * sizeof(int));
	unsigned long jumpMultipler = fmod(pow(FIRSTMULTI, numSeeds), MODULUS);
	for(unsigned char counter = 0; counter < numSeeds; counter++)
		seeds[counter] = jumpMultipler * (counter + 1) % (MODULUS - 1);
	return seeds;
}
