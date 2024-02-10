#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#define _USE_MATH_DEFINES 
#include <math.h>

#ifndef M_PI
#define M_PI  3.14159265358979323846
#endif

uint64_t xseed;

uint64_t splitmix64() {
	uint64_t z = (xseed += 0x9e3779b97f4a7c15);
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	return z ^ (z >> 31);
}



static uint64_t st[4];

static inline uint64_t rotl(const uint64_t x, int k) {
	return (x << k) | (x >> (64 - k));
}

/* seeding function . Supply it with any number. Call it once at the beginning of the program*/


//----------------------------------------------------------------
/*  The following two functions were written in 2018 by David Blackman and Sebastiano Vigna and were put in the public domain */

void init (uint64_t seed)
{
	xseed=seed;
	st[0] = splitmix64();
	st[1] = splitmix64();
	st[2] = splitmix64();
	st[3] = splitmix64();	
}
	
/* pseudo randon number generator based on xorshift, has a period of 2^{256}-1 */
uint64_t gen64uint(void) {
	const uint64_t result = rotl(st[1] * 5, 7) * 9;

	const uint64_t t = st[1] << 17;

	st[2] ^= st[0];
	st[3] ^= st[1];
	st[1] ^= st[2];
	st[0] ^= st[3];
	st[2] ^= t;
	st[3] = rotl(st[3], 45);

	return result;
}
