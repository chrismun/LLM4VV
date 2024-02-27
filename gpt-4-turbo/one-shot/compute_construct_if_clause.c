#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "acc_testsuite.h" // Assuming acc_testsuite.h is available for defining constants and utility functions

#ifndef TEST_COMPUTE_IF
// TEST_COMPUTE_IF:kernels,if,V:1.0-2.7
int test_compute_if() {
    int err = 0;
    const int n = 10000;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    int condition = rand() % 2; // Randomly enable or disable the execution of the OpenACC region

    for (int i = 0; i < n; ++i) {
        a[i] = rand() / (real_t)(RAND_MAX / 100);
        b[i] = 0;
    }

    #pragma acc data copyin(a[0:n]) copyout(b[0:n])
    {
        #pragma acc kernels if(condition)
        {
            #pragma acc loop
            for (int i = 0; i < n; ++i) {
                b[i] = a[i];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (condition) {
            if (fabs(b[i] - a[i]) > PRECISION) {
                err++;
            }
        } else {
            if (fabs(b[i]) > PRECISION) { // b[i] should remain 0 since kernels should not execute
                err++;
            }
        }
    }

    free(a);
    free(b);
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;

#ifndef TEST_COMPUTE_IF
    for (int i = 0; i < NUM_TEST_CALLS; ++i) {
        failed += test_compute_if();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif
    
    return failcode;
}