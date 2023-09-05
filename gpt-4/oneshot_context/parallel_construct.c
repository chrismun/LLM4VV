#include <stdio.h>
#define N 100000

void main() {
   float a[N], b[N], c[N];
   
   // Initialize a and b with random values
   for(int i = 0; i < N; i++) {
      a[i] = i;
      b[i] = i;
   }

   #pragma acc parallel loop copyin(a[0:N], b[0:N]) copyout(c[0:N])
   for(int i = 0; i < N; i++) {
      c[i] = a[i] + b[i];
   }

   // Print first 5 results for sanity check
   for(int i = 0; i < 5; i++) {
      printf("%f ", c[i]);
   }
   printf("\n");
}