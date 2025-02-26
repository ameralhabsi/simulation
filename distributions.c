/*
   random number generator with multiple probability distribution
   written by Amer Alhabsi
   Copyright 2022 Amer Alhabi
   
   License: 3-clause BSD 
   
*/
   
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <time.h>
#define _USE_MATH_DEFINES 
#include <math.h>

#include "distributions.h"

#ifndef M_PI
#define M_PI  3.14159265358979323846
#endif


void init (uint64_t seed);
uint64_t gen64uint(void) ;
 
//----------------------------------------------------------------

/*-------------------------------------------------------*/
/* doubles include 53 bits mantissa, so we need two 32-bits rands. 
https://stackoverflow.com/questions/55766058/how-can-i-generate-random-doubles-in-c

*/
double gen_uniform53() {
    uint64_t r53 = gen64uint() >> 11;
    return (double)r53 / 9007199254740991.0; // 2^53 - 1
}

double gen_uniform()
{
	return gen_uniform53();
}

/*-------------------------------------------------------*/
/* Generates discrete (a, b) inclusive. Caller ensures a<b */
int gen_discrete(int a, int b)
{
	double u1;
	u1 = gen_uniform53();
	return (int) floor(u1 * (b-a+1)) + a;
}

/*-------------------------------------------------------*/
/* Generates Gaussian (Normal) random numbers */
double gen_gauss()
{
	double u1, u2, z;

	u1 = gen_uniform53();
	u2 = gen_uniform53();

	z = sqrt(2.0 * log(1.0 / (1.0 - u1)));
	return (z * cos(2*M_PI * u2));
}


/*-------------------------------------------------------*/
/* Generates Rayleigh-distributed random numbers */
double gen_rayleigh()
{
	double u1;
	u1 = gen_uniform53();
	//z = sqrt(2.0 * log(1.0 / (1.0 - u1))); /* this is the transformation*/
	return (sqrt(-2.0 * log(1.0 - u1)));	//one division op is removed for speed
}

/*-------------------------------------------------------*/
/* binary 0,1 */
int gen_binary()
{
	double x;
	x = gen_uniform53();

	if (x < 0.5)
		return 0;
	else
		return 1;
}

/*-------------------------------------------------------*/
/* anti-podal -1, 1 */
int gen_antipodal()
{
	double x;
	x = gen_uniform53();

	if (x < 0.5)
		return -1;
	else
		return 1;
}

/*--------------------------------------------------------*/

int gen_bernoulli(double p)
{
	double x;
	x = gen_uniform53();

	if (x < p)
		return 1;
	else
		return 0;
}

/*--------------------------------------------------------*/

double gen_weibull(double k, double lambda)
{
	double x, z;
	x = gen_uniform53();

	z = pow(lambda*(-log(1-x)), 1.0/k);
	return z;
}

/*-------------------------------------------------------*/
/* Generates exponential distribution random numbers */
double gen_exponential(double lambda)
{
	double u1, z;

	u1 = gen_uniform53();
	
	z = -log(u1)/lambda;
	return (z);
}
/*--------------------------------------------------------*/
double cauchy()
{
	double u1, z;
	u1 = gen_uniform53();
	z=tan(M_PI*(u1-0.5));
	return z;
}
/*--------------------------------------------------------*/
int poisson(double lambda)
{
	double L, p, u1;
	int k;
	
	L=exp(-lambda);
	k=0;
	p=1;
	do{
		k++;
		u1 = gen_uniform53();
		p = p*u1;

	}while(p>L);

	return (k-1);
}

/*--------------------------------------------------------*/
/* Q-function: right tail of Gaussian (Normal) distribution
   Q(x) = 0.5 * erfc(x/sqrt(2))
 */
double Q(double x)
{
	return (0.5 * erfc(x * M_SQRT1_2));
}

/*--------------------------------------------------------*/
/* Phi-function: left tail of Gaussian (Normal) distribution, N(0,1)
   phi(x) = 1 - Q(x)
 */
double phi(double x)
{
	return (1.0 - Q(x));
}
