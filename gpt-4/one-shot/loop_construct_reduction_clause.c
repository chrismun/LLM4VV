#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 10000

int main() {
  int i;
  float sum, a[SIZE];

  // Initialize array
  for (i = 0; i < SIZE; ++i) {
    a[i] = (float)i + 1;
  }

  sum = 0.0;

  // OpenACC parallel loop with reduction
  #pragma acc parallel loop reduction(+:sum)
  for (i = 0; i < SIZE; ++i) {
    sum += a[i];
  }

  printf("Total sum = %f\n", sum);

  // Verify the result
  float expected_sum = (float)((SIZE/2.0) * (SIZE + 1));
  
  if (abs(sum - expected_sum) > 1e-5) {
    printf("Test failed. Sum should have been %f\n", expected_sum);
    return -1;
  }

  printf("Test passed.\n");
  return 0;
}