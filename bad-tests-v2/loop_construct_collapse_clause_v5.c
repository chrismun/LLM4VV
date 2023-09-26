#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include <math.h>

#define SIZE 1000
#define TOLERANCE 0.001f

void evaluate(float* result, float* input1, float* input2, int n) {
#pragma acc kernels loop collapse(2)
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      result[i*n + j] = input1[i*n + j] + input2[i*n + j];
    }
  }
}

int main() {
  // Allocate space for the arrays
  float* input1 = (float*) malloc(SIZE*SIZE*sizeof(float));
  float* input2 = (float*) malloc(SIZE*SIZE*sizeof(float));
  float* result = (float*) malloc(SIZE*SIZE*sizeof(float));
  
  // Populate the input arrays and initialize the result array
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      input1[i*SIZE + j] = i+1;
      input2[i*SIZE + j] = j+1;
      result[i*SIZE + j] = 0.0f;
    }
  }

  // Test the collapse clause
  evaluate(result, input1, input2, SIZE);
  
  // Verify the results
  int pass = 1;
  for (int i = 0; i < SIZE; i++) {
    for (int j = 0; j < SIZE; j++) {
      float expected = input1[i*SIZE + j] + input2[i*SIZE + j];
      if (fabsf(result[i*SIZE + j] - expected) > TOLERANCE) {
        pass = 0;
        printf("Test failed at position (%d, %d), expected: %f, got: %f\n", i, j, expected, result[i*SIZE + j]);
      }
    }
  }
  
  if (pass) {
    printf("Test passed!\n");
  } else {
    printf("Test failed!\n");
  }

  // Free the space allocated for the arrays
  free(input1);
  free(input2);
  free(result);

  return 0;
}