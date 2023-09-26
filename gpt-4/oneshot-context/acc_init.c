#include <stdio.h>
#include <openacc.h>

int main()
{
  // Initialize the device
  acc_init(acc_device_default);

  // number of elements and bytes
  int n = 1<<20;
  int nbytes = n * sizeof(int);

  // alloc host memory
  int* h_x = (int*)malloc(nbytes);

  // alloc device memory
  int* d_x;
  d_x = (int*)acc_malloc(nbytes);

  // initialize host data
  for(int i=0; i<n; i++) {
    h_x[i] = i;
  }

  // copy host data to the device
  acc_memcpy_to_device(d_x, h_x, nbytes);

  // copy data from device back to host
  acc_memcpy_from_device(h_x, d_x, nbytes);

  // check result
  for(int i=0; i<n; i++) {
    if(h_x[i] != i) {
      printf("FAILED at i=%d! Got: %d, expected: %d\n", i, h_x[i], i);
      break;
    }
  }

  // free memory
  acc_free(d_x);
  free(h_x);

  return 0;