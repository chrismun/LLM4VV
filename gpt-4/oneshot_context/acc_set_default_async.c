#include <openacc.h>
#include <stdio.h>

void test() {
  int async_arg = 1;
  int N = 1000;
  double a[N];

  acc_set_device_type(acc_device_nvidia);  // set device to nvidia
  acc_init(acc_device_nvidia);
  
  //Set the async
  acc_set_default_async(async_arg);

  // Perform some computation in parallel using this queue
  #pragma acc parallel loop async
  for (int i = 0; i < N; i++) {
    a[i] = i * 2.0;
  }

  // Wait for all async to complete
  acc_wait_all();

  // Print the first 5 elements to confirm computation
  for (int i = 0; i < 5; i++) {
    printf("%f ", a[i]);
  }
  printf("\n");
}

int main() {
  test();
  return 0;