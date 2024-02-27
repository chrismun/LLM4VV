#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:kernels,async,wait,V:1.0-2.7
int test1(){
    int err = 0;
    const int n = 10000;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    // Initialize arrays
    for (int i = 0; i < n; ++i){
        a[i] = (real_t)i;
        b[i] = (real_t)-i;
    }

    // Perform operations on different async queues
    #pragma acc parallel loop async(1) copyout(b[0:n])
    for (int i = 0; i < n; ++i){
        b[i] = a[i] * 2.0;
    }

    #pragma acc parallel loop async(2) copy(a[0:n])
    for (int i = 0; i < n; ++i){
        a[i] = sqrt(a[i]);
    }

    // Wait for both operations to complete
    #pragma acc wait async(1) async(2)

    // Verify the results
    for (int i = 0; i < n; ++i){
        if (fabs(b[i] - 2.0 * a[i] * a[i]) > PRECISION){
            err++;
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
    failed = test1();
    if (failed != 0){
        printf("Test1 failed with %d errors.\n", failed);
        failcode = 1;
    } else {
        printf("Test1 passed.\n");
    }
#endif
    return failcode;
}