#include "openacc.h"
#include <stdlib.h>
#include <stdio.h>

#pragma acc routine seq
float square(float a) {
  return a*a;
}

int test1() {
  int n = 100000;
  float *in, *out, *verify;
  int errors = 0;
    
  in = (float*)malloc(n*sizeof(float));
  out = (float*)malloc(n*sizeof(float));
  verify = (float*)malloc(n*sizeof(float));

  for(int i=0; i<n; i++) {
    in[i] = (float)rand()/(float)(RAND_MAX);
    verify[i] = square(in[i]);
  }
    
  #pragma acc data copyin(in[0:n]) copyout(out[0:n])
  {
    #pragma acc parallel loop
    for(int i=0; i<n; i++) {
      out[i] = square(in[i]);
    }
  }
    
  for(int i=0; i<n; i++) {
    if(abs(out[i] - verify[i]) > 1.0e-7) {
      errors++;
    }
  }

  free(in);
  free(out);
  free(verify);
  
  return errors;
}

int main() {
  if(test1() == 0) {
    printf("Routine Directive Test Passed\n");
    return EXIT_SUCCESS;
  } else {
    printf("Routine Directive Test Failed\n");
    return EXIT_FAILURE;
  }
}