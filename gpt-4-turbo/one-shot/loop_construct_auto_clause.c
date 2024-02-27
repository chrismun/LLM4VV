#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "acc_testsuite.h"

#ifndef T2
// T2:kernels,loop,auto,V:1.0-2.7
int test2() {
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *auto_b = (real_t *)malloc(n * sizeof(real_t));
    real_t *no_auto_b = (real_t *)malloc(n * sizeof(real_t));

    // Initialize array `a` with random values
    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copyin(a[0:n]) copyout(auto_b[0:n])
    {
        #pragma acc kernels
        {
            #pragma acc loop auto
            for(int x = 0; x < n; ++x){
                auto_b[x] = a[x] + 1;
            }
        }
    }

    // Serial loop for comparison
    for(int x = 0; x < n; ++x){
        no_auto_b[x] = a[x] + 1;
    }
    
    // Validate output
    for (int x = 0; x < n; ++x) {
        if (fabs(auto_b[x] - no_auto_b[x]) > PRECISION) {
            err++;
        }
    }

    free(a);
    free(auto_b);
    free(no_auto_b);

    return err;
}
#endif

int main() {
    int failcode = 0;

    #ifndef T2
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test2();
    }
    if (failed != 0) {
        failcode += (1 << 1);
    }
    #endif

    return failcode;
}