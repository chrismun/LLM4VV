#include <stdio.h>
#include <stdlib.h>

#define SIZE 100

int main()
{
  int *a = (int*) malloc(SIZE * sizeof(int));
  int i;

  // Initialize array in the host
  for(i = 0; i < SIZE; i++)
    a[i] = i;

  // Create clause in OpenACC. The array a is created on the device, 
  // and its contents remain unitialized (not copied from the host).
  #pragma acc data create(a[0:SIZE])
  {
    #pragma acc parallel loop
    for(i = 0; i < SIZE; i++){
      // Since we did not copy data from host, the values here are undefined
      // Let's assign new values
      a[i] = i * 2;
    }

    // When the data region ends, 'a' still exists in the device memory,
    // because it was created there (not just copied).
    // But it is not automatically copied back to the host.
  }

  // Copy data from device to host manually
  #pragma acc update host(a[0:SIZE])

  // Check results
  for(i = 0; i < SIZE; i++){
    if(a[i] != i*2) {
      printf("Test failed at index %d! Got %d, expected %d\n", i, a[i], i*2);
      return -1;
    }
  }

  printf("Test passed!\n");
  free(a);

  return 0;
}