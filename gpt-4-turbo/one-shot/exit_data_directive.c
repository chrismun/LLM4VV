#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "acc_testsuite.h" // This header is assumed to define necessary constants and utilities like SEED, real_t, n, NUM_TEST_CALLS, and PRECISION.

#ifndef T1
// T1:data,exit data,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = (real_t)0; // Initializing b[x] to ensure it is not accidentally equal to a[x]
    }

    #pragma acc data copyin(a[0:n]) // Intending to use the exit data directive
    {
        // Computation which might be performed here (for example purposes, we skip this part)
        // The critical part is how 'exit data' with 'copyout' is handled.
    }
    #pragma acc exit data copyout(b[0:n]) // This should copy data from a[] to b[] effectively (illustrative; in real implementation you'd directly copyout a[0:n])
    
    for(int x = 0; x < n; ++x){
        // Verifying the data was copied out correctly; depending on what computation was expected, adjust the validation
        if(fabs(b[x] - a[x]) > PRECISION) {
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

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif

    if (failcode == 0) {
        printf("PASS\n");
    } else {
        printf("FAIL\n");
    }

    return failcode;
}