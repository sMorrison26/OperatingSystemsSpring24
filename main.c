#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>

int main(int argc, char** argv){
  int n = atoi(argv[1]);
  int NCPU = atoi(argv[2]);
  int seed = atoi(argv[3]);
  float lambda = atof(argv[4]);
  int upperBound =atoi(argv[5]);
  
  // Check to see if command line args are parsed properly
  // printf("%d, %d, %d, %.3f, %d\n", n, NCPU, seed, lambda, upperBound);
  
  return 0;
}