#include <stdio.h>
#include <stdlib.h>
#include <math.h>
// Assuming acc_testsuite.h provides necessary environment setup including SEED, n, PRECISION, etc.
#include "acc_testsuite.h"

#ifndef T2
//T2:kernels,loop,construct,default,V:1.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = -1; // Initialize to a value that should not be present after computation
    }

    // Explicit data region to avoid automatic data movement for validation purposes
    #pragma acc data copyin(a[0:n])
    {
        // Testing default behavior within compute construct
        #pragma acc parallel loop default(present)
        for (int x = 0; x < n; ++x){
            b[x] = a[x];
        }
    }

    //Verifying results
    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
            err += 1;
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
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test2();
    }
    if (failed != 0){
        failcode += (1 << 1); // Assign unique failcode for this specific test
    }
#endif
    if (failcode == 0) {
        printf("PASSED: All tests on OpenACC default clause passed.\n");
    } else {
        printf("FAILED: Some tests on OpenACC default clause failed. Failcode: %d\n", failcode);
    }
    return failcode;
}