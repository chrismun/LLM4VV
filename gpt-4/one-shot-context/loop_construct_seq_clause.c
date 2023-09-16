#include <stdio.h>
#include <openacc.h>

int main() {
  int numErrors = 0;
  const int N = 10000;
  float a[N], b[N];

  // initialization of the vectors
  for(int n = 0; n < N; n++) {
    a[n] = (float)n;
    b[n] = 0.0f;
  }

  #pragma acc data copyin(a[0:N]) copyout(b[0:N])
  {
    #pragma acc parallel loop seq
      for(int n = 0; n < N; n++) {
          b[n] = a[n];
      }
  }

  // verify results
  for(int n = 0; n < N; n++) {
    if(a[n] != b[n]) {
      printf("Error: a[%d] = %f, b[%d] = %f\n", n, a[n], n, b[n]);
      numErrors++;
    }
  }

  printf("Total Errors: %d\n", numErrors);

  return 0;
}