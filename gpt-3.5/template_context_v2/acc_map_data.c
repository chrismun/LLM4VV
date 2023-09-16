#include "acc_testsuite.h"
#ifndef T1
// T1: acc map data, V: 2.7-3.3
int test1() {
  int err = 0;
  size_t bytes = N * sizeof(float);
  float *a_host, *b_host;
  float *a_device, *b_device;

  a_host = (float *)malloc(bytes);
  b_host = (float *)malloc(bytes);
  CUDA_CHECK(cudaMalloc(&a_device, bytes));
  CUDA_CHECK(cudaMalloc(&b_device, bytes));

  // Initialize host arrays
  for (int i = 0; i < N; i++) {
    a_host[i] = rand() / (float)RAND_MAX;
    b_host[i] = 0.0f;
  }

  // Transfer data from host to device
  CUDA_CHECK(cudaMemcpy(a_device, a_host, bytes, cudaMemcpyHostToDevice));

#pragma acc data copyin(a_device[0:N]) copyout(b_device[0:N])
  {
#pragma acc parallel loop map(data: b_device[0:N])
    for (int i = 0; i < N; i++) {
      b_device[i] = a_device[i] + 1.0f;
    }
  }

  // Transfer data from device to host
  CUDA_CHECK(cudaMemcpy(b_host, b_device, bytes, cudaMemcpyDeviceToHost));

  // Validate the result
  for (int i = 0; i < N; i++) {
    if (b_host[i] != (a_host[i] + 1.0f)) {
      err = 1;
      break;
    }
  }

  // Cleanup
  free(a_host);
  free(b_host);
  cudaFree(a_device);
  cudaFree(b_device);

  return err;
}
#endif

int main() {
  int failcode = 0;
  int failed;

#ifndef T1
  failed = 0;
  for (int x = 0; x < NUM_TEST_CALLS; ++x) {
    failed = failed + test1();
  }
  if (failed != 0) {
    failcode = failcode + (1 << 0);
  }
#endif

return failcode;
}