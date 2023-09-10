#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdbool.h>

#ifndef T1
/*T1:loop construct device_type clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    const int size = 1000;
    int *a = (int*) malloc(size * sizeof(int));
    int *b = (int*) malloc(size * sizeof(int));
  
    srand(SEED);

    // Initialize array
    for (int i = 0; i < size; i++) {
        a[i] = rand();
    }

    #pragma acc data copy(a[0:size], b[0:size])
    {
      #pragma acc parallel loop device_type(nvidia)
      for (int i = 0; i < size; i++) {
          b[i] = a[i];
      }
    }

    // Check if the arrays are equal
    for (int i = 0; i < size; i++) {
      if (a[i] != b[i]) {
          err = 1;
          break;
      }
    }

    free(a);
    free(b);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}