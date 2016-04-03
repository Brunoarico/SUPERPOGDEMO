#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h> 
#include <math.h>
#include <time.h>
#define G 6.67E-11
#include "ship.h"

void *mallocc (size_t nbytes)
{
   void *ptr;
   ptr = malloc (nbytes);
   if (ptr == NULL) {
      printf ("Socorro! malloc devolveu NULL!\n");
      exit (EXIT_FAILURE);
   }
   return ptr;
}

double modulo (float x[]) {
    return sqrt( pow (x[0], 2) + pow (x[1], 2));
}

float distEucl (float posA[2], float posB[2]) {
    return sqrt (pow (posA[0] - posB[0], 2) + pow (posA[1] - posB[1], 2));
}

double to_rad(float  deg) {
    return deg * (M_PI / 180.0);
}

double to_deg(float rad) {
    return rad * (180.0 / M_PI);
}

float gravit (float p1[], float p2[], float M, float m) { //atração gravitacional

    return G * M * m / pow (distEucl (p1, p2), 2);
}

float orbtVel (float r, float M) { //velocidade de orbita
    return sqrt (G * M/r);
}
    
    
