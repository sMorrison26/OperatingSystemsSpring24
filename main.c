#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

//exponential distribution psuedo-random number generator
int next_exp(unsigned int seed, float max, float lambda){
  srand48(seed);

                      /* uniform to exponential distribution: */
                      /*                                      */
                      /*       -ln(1-r)                       */
                      /*  x = ----------                      */
  double sum = 0;     /*        lambda                        */
  double min = 0;
  int iterations = 1000000;     /* <== make this number very large */
                                /* average should be 1/lambda ==> 1000 */

  for (int i=0; i<iterations; i++){

    double r = drand48();         /* uniform dist [0.00,1.00) -- also check out random() */
    double x = -log(r) / lambda;  /* log() is natural log */

    /* avoid values that are far down the "long tail" of the distribution */
    if ( x > 8000 ) { i--; continue; }

    // if ( i < 20 ) printf( "x is %lf\n", x );
    sum += x;
    if ( i == 0 || x < min ) { min = x; }
    if ( i == 0 || x > max ) { max = x; }
  }

  return sum / iterations;
}


int main(int argc, char** argv){
  if (argc != 6){
    fprintf(stderr,"ERROR: \nUSAGE: <n> <ncpu> <seed> <lambda> <upper_bound>");
  }
  int n = atoi(argv[1]);
  int nCPU = atoi(argv[2]);
  int seed = atoi(argv[3]);
  float lambda = atof(argv[4]);
  int upperBound = atoi(argv[5]);
  
  // Check to see if command line args are parsed properly
  // printf("%d, %d, %d, %.3f, %d\n", n, NCPU, seed, lambda, upperBound);
  int avg = next_exp(seed, upperBound, lambda);
  printf("%d\n", avg);
  
  return 0;
}