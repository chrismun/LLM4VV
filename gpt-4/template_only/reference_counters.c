#include <stdio.h>
#include <openacc.h>
#include <stdlib.h>

#define N 1000000

void check(int *a, int *b, int *c) {
  int i;
  for(i=0; i<N; i++) {
    if(c[i] != a[i] + b[i]) {
      printf("Error: value c[%d] = %d instead of %d\n", i, c[i], a[i] + b[i]);
      exit(1);
    }
  }
}

void vecadd(int *a, int *b, int *c) {
  int i;
  #pragma acc kernels
  for(i=0; i<N; i++) {
    c[i] = a[i] + b[i];
  }
}

int main() {
  int *a=(int*) malloc(N*sizeof(int));
  int *b=(int*) malloc(N*sizeof(int));
  int *c=(int*) malloc(N*sizeof(int));

  // Initialize a and b
  for(int i=0; i<N; i++) {
    a[i] = i;
    b[i] = i * 1000;
  }

  vecadd(a, b, c);

  check(a, b, c);

  printf("finished\n");
  return 0;
}