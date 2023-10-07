#include "acc_testsuite.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

#define SIZE 512

#define TOLERANCE 0.01

void initialize(float* a, float* b, float* c, int size) {
  for(int i = 0; i < size; i++) {
    for(int j = 0; j < size; j++) {
      a[i*size + j] = (float)rand()/RAND_MAX;
      b[i*size + j] = (float)rand()/RAND_MAX;
      c[i*size + j] = 0.0f;
    }
  }
}

void verify(float* a, float* b, float* c, int size) {
  float tmp;
  int i, j, k;
  for(i = 0; i < size; i++) {
    for(j = 0; j < size; j++) {
      tmp = 0.0f;
      for(k = 0; k < size; k++) {
        tmp += a[i*size+k] * b[k*size+j];
      }
      if(fabs(c[i*size+j] - tmp) > TOLERANCE) {
        printf("Verification failed! Expected %f, but got %f\n", tmp, c[i*size+j]);
        exit(1);
      }
    }
  }
}

int main() {
  float *a, *b, *c;
  
  a = (float*)malloc(SIZE * SIZE * sizeof(float));
  b = (float*)malloc(SIZE * SIZE * sizeof(float));
  c = (float*)malloc(SIZE * SIZE * sizeof(float));
  
  initialize(a, b, c, SIZE);
  
  #pragma acc data copyin(a[0:SIZE*SIZE], b[0:SIZE*SIZE]) copyout(c[0:SIZE*SIZE])
  {
    #pragma acc parallel loop gang worker
    for(int i = 0; i < SIZE; i++) {
      #pragma acc loop gang worker
      for(int j = 0; j < SIZE; j++) {
        float tmp = 0.0f;
        #pragma acc loop seq
        for(int k = 0; k < SIZE; k++) {
          tmp += a[i*SIZE + k] * b[k*SIZE + j];
        }
        c[i*SIZE + j] = tmp;
      }
    }
  }
  
  verify(a, b, c, SIZE);
  
  free(a);
  free(b);
  free(c);
  
  return 0;
}