#include <openacc.h>
#include <stdio.h>

int async_test() {
  int arr[1024];
  int n = 1024;
  int data_error = 0;

  for (int i = 0; i < n; i++) {
     arr[i] = i;  
  }

  #pragma acc data copy(arr[0:1024])
  {
    #pragma acc kernels async //async construct
    {
      for (int i = 0; i < n; i++) {
         arr[i] = arr[i] + i;
      }
    }
    acc_wait_async(1); //wait for async to finish
  }

  for (int i = 0; i < n; i++) {
      if(arr[i] != 2*i) {
        fprintf(stderr, "Error at position %d, expected %d, found %d\n", i, i+i, arr[i]);
        data_error = 1;
    }
  }
  return data_error;
}


int main() {
  int significant_error = 0;

  significant_error += async_test();
  
  if (significant_error) {
    printf("Failed\n");
  } else {
    printf("Passed\n");
  }

  return 0;
}