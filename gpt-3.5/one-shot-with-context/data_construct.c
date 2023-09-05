#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
  int* a = (int*) malloc(SIZE * sizeof(int));
  int* b = (int*) malloc(SIZE * sizeof(int));

  // Initialize array a
  for (int i = 0; i < SIZE; i++) {
    a[i] = i;
    b[i] = 0;
  }

  // Copy array a to device memory
  #pragma acc enter data copyin(a[0:SIZE])

  // Update array b on the device
  #pragma acc parallel loop present(a, b)
  for (int i = 0; i < SIZE; i++) {
    b[i] = a[i] + 1;
  }

  // Copy array b back to host memory
  #pragma acc exit data copyout(b[0:SIZE])

  // Verify the results
  int success = 1;
  for (int i = 0; i < SIZE; i++) {
    if (b[i] != a[i] + 1) {
      success = 0;
      break;
    }
  }

  if (success) {
    printf("Data construct test passed\n");
  } else {
    printf("Data construct test failed\n");
  }

  // Free memory
  free(a);
  free(b);

  return 0;