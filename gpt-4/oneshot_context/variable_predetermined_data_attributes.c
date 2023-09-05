#include <stdio.h>
#include <openacc.h>

int main(){

  const int size = 100;
  float a[size];
  float b[size];
  float sum = 0;

  // Initialize Array
  for(int i=0; i<size; i++) {
    a[i] = i;
    b[i] = i;
  }

  #pragma acc data copyin(a[0:size], b[0:size]) copy(sum)
  {
    #pragma acc parallel loop reduction(+:sum)
    for(int i=0; i<size; i++) {
      sum += a[i] * b[i];
    }

    #pragma acc parallel loop private(i)
    for(int i=0; i<size; i++) {
      a[i] = b[i] + sum;
    }

    #pragma acc parallel num_gangs(1)
    {
      float local_sum = 0;
      #pragma acc loop gang reduction(+:local_sum)
      for(int i=0; i<size; i++) {
	local_sum = a[i] + local_sum;
      }
    }
  }

  printf("Sum = %f\n", sum);

  return 0;