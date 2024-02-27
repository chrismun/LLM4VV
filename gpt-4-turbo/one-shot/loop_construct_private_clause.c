#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:loop,private,V:1.0-2.7
int test_private_clause() {
    int err = 0;
    srand(SEED);
    const int n = 100;
    real_t *results = (real_t *)malloc(n * sizeof(real_t));

    // Initialize results to 0.
    for (int i = 0; i < n; ++i){
        results[i] = 0.0;
    }

    #pragma acc data copy(results[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop private(i)
            for (int i = 0; i < n; ++i) {
                real_t temp = (real_t)i + 1;
                results[i] = temp;
            }
        }
    }

    // Validation
    for (int i = 0; i < n; ++i) {
        if (fabs(results[i] - ((real_t)i + 1)) > PRECISION) {
            err += 1;
        }
    }

    free(results);
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = test_private_clause();
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}