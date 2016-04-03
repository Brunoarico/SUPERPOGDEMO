#ifndef phisics
#define phisics

#include <stdio.h>
#include "ship.h"


void *mallocc (size_t nbytes);

double modulo (float x[]);

float distEucl (float posA[2], float posB[2]);

double to_rad(float  deg);

double to_deg(float rad);

float gravit (float p1[], float p2[], float M, float m);

float orbtVel (float r, float M);

#endif
