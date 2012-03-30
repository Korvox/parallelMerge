/* Inline threadsafe RNG header
 * @author Matthew Scheirer
 * @license GPL v3 */
 
#ifndef RNG
#define RNG

#include <stdlib.h>
#include <math.h>

#define MULTIPLIER 48271
#define MODULUS 2147483647
#define FIRSTMULTI 7

int lehmerRandom(int);
int * generateSeeds(unsigned char);

#endif
