/*
   random number generator with multiple probability distribution
   written by Amer Alhabsi
   Copyright 2022 Amer Alhabi
   
   License: 3-clause BSD
   
*/
#ifndef DISTRIBITION_H
#define DISTRIBITION_H
#include <stdint.h>
#include <inttypes.h>

double gen_uniform53();
double gen_uniform();
int gen_discrete(int a, int b);
double gen_gauss();
double gen_rayleigh();
int gen_binary();
int gen_antipodal();
int gen_bernoulli(double p);
int gen_weibull(double k, double lambda);
double gen_exponential(double lambda);
double Q(double x);
double phi(double x);
#endif
