#include "openacc.h"
#include "assert.h"

int main() {
  const int N = 100;
  int host_data[N];
  int* dev_data;

  // Initialize host data.
  for(int i=0; i<N; ++i) {
    host_data[i] = i;
  }

  // Allocate device data.
  dev_data = (int*)acc_malloc(N * sizeof(int));

  // Attach host array to device pointer.
  acc_attach(dev_data, host_data, N * sizeof(int));

  // Check that data still match after attaching both arrays.
  #pragma acc parallel loop present(dev_data[:N])
  for(int i=0; i<N; ++i) {
    assert(host_data[i] == dev_data[i]);
  }

  // Modify the device data.
  #pragma acc parallel loop present(dev_data[:N])
  for(int i=0; i<N; ++i) {
    dev_data[i] += 1;
  }

  // Check that data still match after modifying the device array.
  #pragma acc parallel loop present(dev_data[:N])
  for(int i=0; i<N; ++i) {
    assert(host_data[i] != dev_data[i]);
  }

  // Detach the host array from the device pointer.
  acc_detach(dev_data);

  // Check that data don't match after detaching both arrays.
  #pragma acc parallel loop present(dev_data[:N])
  for(int i=0; i<N; ++i) {
    assert(host_data[i] != dev_data[i]);
  }

  // Free device data.
  acc_free(dev_data);

  return 0;
}