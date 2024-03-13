#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

//exponential distribution psuedo-random number generator
double next_exp(int max, float lambda){
  // Apply the exponential distribution formula with scaling to limit the maximum value
  double result = 0.0;

  // Generate a random number from a uniform distribution
  double random_num = drand48();
  while (1) {
    result = -log(random_num) / (lambda);
    if (result > max){
      random_num = drand48();
      continue;
    }
    else
      return result;
  }
}

int checkNextExp(int upperBound, float lambda){
  int nextExp = ceil(next_exp(upperBound, lambda));
  while (nextExp >= upperBound){
    nextExp = ceil(next_exp(upperBound, lambda));
  }
  return nextExp;
}

int main(int argc, char** argv){

  if (argc != 6){
    fprintf(stderr,"ERROR: USAGE: <n> <ncpu> <seed> <lambda> <upper_bound>\n");
    return EXIT_FAILURE;
  }

  int n = atoi(argv[1]);
  int nCPU = atoi(argv[2]);
  int seed = atoi(argv[3]);
  float lambda = atof(argv[4]);
  int upperBound = atoi(argv[5]);

  // Error check n
  if (n > 26 || n < 0) {
    fprintf(stderr, "ERROR: incorrect number of processes\n");
    return EXIT_FAILURE;
  }
  //# CPU processes > total processes count
  if (nCPU > n || nCPU < 0){
    fprintf(stderr,"ERROR: incorrect number of CPU processes\n");
    return EXIT_FAILURE;
  }


  printf("<<< PROJECT PART I -- process set (n=%d) with %d CPU-bound process",n,nCPU);
  if (nCPU != 1) printf("es >>>\n");
  else printf(" >>>\n");

  // Check to see if command line args are parsed properly
  // printf("%d, %d, %d, %.3f, %d\n", n, NCPU, seed, lambda, upperBound);
  srand48(seed);
  for (int i=0; i<n; i++){
    int arrivalTime = next_exp(upperBound, lambda);
    int CPUBursts = ceil(drand48()*64);
    char processLetter = (char) 65 + i;
    int IOBoundProcesses = n - nCPU;
    if (i>=IOBoundProcesses){
      // CPU BOUND
      printf("CPU-bound process %c: arrival time %dms; %d CPU burst",processLetter,arrivalTime,CPUBursts);
      if (CPUBursts != 1) printf("s:\n");
      else printf(":\n");

      for (int j=0; j<CPUBursts; j++){
        int nextExp = checkNextExp(upperBound,lambda);
        int CPUBurstTime = ceil(nextExp)*4;
        if (j==CPUBursts-1){
          //only cpu
          printf("--> CPU burst %dms\n",CPUBurstTime);
        } else {
          //CPU & I/O
          int nextExp = checkNextExp(upperBound,lambda);
          int IOBurstTime = (ceil(nextExp)*10)/8;
          printf("--> CPU burst %dms --> I/O burst %dms\n",CPUBurstTime,IOBurstTime);
        }
      }
    } else {
      // IO BOUND
      printf("I/O-bound process %c: arrival time %dms; %d CPU burst",processLetter,arrivalTime,CPUBursts);
      if (CPUBursts != 1) printf("s:\n");
      else printf(":\n");

      for (int j=0; j<CPUBursts; j++){
        int nextExp = checkNextExp(upperBound,lambda);
        int CPUBurstTime = nextExp;
        if (j==CPUBursts-1){
          //only cpu
          printf("--> CPU burst %dms\n",CPUBurstTime);
        } else {
          //CPU & I/O
          nextExp = checkNextExp(upperBound,lambda);
          int IOBurstTime = ceil(nextExp)*10;
          printf("--> CPU burst %dms --> I/O burst %dms\n",CPUBurstTime,IOBurstTime);
        }
      }
    }
  }
  return EXIT_SUCCESS;
}