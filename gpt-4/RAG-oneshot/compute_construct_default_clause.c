#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 1000
#define TOLERANCE 0.001

int main() {
  float *a = (float*) malloc(N * sizeof(float));
  float sum = 0.0;

  for (int i = 0; i < N; i++){
    a[i] = (float)i;
  }

  #pragma acc parallel loop default(none) copy(a[0:N])
  for (int i = 0; i < N; i++){
    a[i] = a[i] * 2.0f;
  }

  
  for (int i = 0; i < N; i++){
    sum = sum + a[i];
  }

  printf("Sum = %f\n",sum);
  if(abs(sum - 3.0f*N*(N-1)) > ((3.0f*N*(N-1))*TOLERANCE)){
    printf("Test failed\n");
    return 1;
  } 
  printf("Test passed\n");
  return 0;
}