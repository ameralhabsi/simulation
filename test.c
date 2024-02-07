/*
   random number generator with multiple probability distribution
   written by Amer Alhabsi
   Copyright 2022 Amer Alhabi
   
   License: 3-clause BSD
   
*/
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include "distributions.h"
#include "rands.h"


#define N 10000000

int main()
{
	int i, k;
	double s0, s2, s4, x;
	int idx;
	int bin[42];
	
	//initialize the RNG
	init(time(NULL));
	
	for(i=0; i<=41; i++)
		bin[i]=0;
	
	s0=s2=s4=0;
	
	/* generate N number with Normal distribution. Calculate
	their mean (s0), their second order moment (s2) and 4th order moment (s4).
	These should be 0, 1 and 3 respectively.
	*/
	for(i=0; i<N; i++){
		x = gen_gauss();
		s0 += x;
		s2 += (x*x);
		s4 += (x*x*x*x);
		
		idx = (int) round(x*10) + 21;
		if(idx<42)
			bin[idx]++;
	}

	printf("sample of the zeroth, second and 4th moments\n");
	printf("s0 = %10.4f\n", s0/N);
	printf("s2 = %10.4f\n", s2/N);
	printf("s4 = %10.4f\n", s4/N);
	
	for(i=0; i<=41; i++){
		for(k=0; k<bin[i]/10000; k++)
			printf("*");
		printf("\n");
	}
	
	return 0;
}
