#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

int main() {
  int n = 256;
  int *a = (int*)malloc(n*sizeof(int));
  int *b = (int*)malloc(n*sizeof(int));
  int *c = (int*)malloc(n*sizeof(int));
  int *d = (int*)malloc(n*sizeof(int));
  int i, dev;
  int correct = 1;

  // Initialize data on host
  for (i=0; i<n; i++) {
    a[i] = i;
    b[i] = 2*i;
    c[i] = 0;
    d[i] = 0;
  }

  /* Execute on device if available */
  #pragma acc data copyin(a[0:n],b[0:n]) copyout(c[0:n]) if(acc_get_num_devices(acc_device_default))
  {
    #pragma acc parallel loop
    for (i=0; i<n; i++) {
        c[i] = a[i] + b[i];
    }
  }

  /* Execute on host if the device is not available */
  #pragma acc data copyin(a[0:n],b[0:n]) copyout(d[0:n]) if(!acc_get_num_devices(acc_device_default))
  {
    for (i=0; i<n; i++) {
        d[i] = a[i] + b[i];
    }
  }

  // Check for correctness
  for (i=0; i<n; i++) {
    if (c[i] != d[i]) {
      correct = 0;
    }
  }

  // Print results
  if (correct) {
    printf("Test passed!\n");
  } else {
    printf("Test failed!\n");
  }

  // Clean up
  free(a);
  free(b);
  free(c);
  free(d);

  return 0;
}