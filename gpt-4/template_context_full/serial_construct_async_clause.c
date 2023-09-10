#include "acc_testsuite.h"
#include <stdlib.h>

int test1() {
    int err = 0;
    int *a, *b, *c, *d;

    // Initialize variables
    a = (int *)malloc(100 * sizeof(int));
    b = (int *)malloc(100 * sizeof(int));
    c = (int *)malloc(100 * sizeof(int));
    d = (int *)malloc(100 * sizeof(int));

    for(int i=0; i<100; i++) {
        a[i] = rand();
        b[i] = rand();
    }

    // Copy data to device
    #pragma acc enter data copyin(a[0:100],b[0:100]) create(c[0:100])

    // Computation on device asynchronously
    #pragma acc serial async
    {
        for(int i = 0; i < 100; i++) {
            c[i] = a[i] + b[i];
        }
    }

    // Copy result back from device asynchronously
    #pragma acc exit data copyout(c[0:100]) async

    #pragma acc wait

    for(int i=0; i<100; i++) {
      d[i] = a[i] + b[i];
      if(c[i] != d[i])
        err = 1;
    }

    // Free up memory
    free(a);
    free(b);
    free(c);
    free(d);

    return err;
}

int main() {
    int failcode = 0;
    srand(SEED);
    int failed;
  
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
  
    if (failed != 0){
        failcode = failcode+ (1 << 0);
    }

    return failcode;
}