/*
   random number generator with multiple probability distribution
   written by Amer Alhabsi
   Copyright 2022 Amer Alhabi
   
   License: 3-clause BSD
   
*/
#ifndef RANDS_H
#define RANDS_H
#include <stdint.h>
#include <inttypes.h>

void init (uint64_t seed);
uint64_t gen64uint(void) ;

#endif
