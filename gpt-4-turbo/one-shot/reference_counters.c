#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:kernels,data,data-region,reference-counters, V:1.0-2.7
int test_reference_counters() {
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0; // Initialize c to zero
    }

    // First region: copyin a & b, create c (implicitly by copyout)
    #pragma acc data copyin(a[0:n], b[0:n])
    {
        #pragma acc kernels copyout(c[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                c[x] = a[x] + b[x];
            }
        }
        // Second region: reuse a, b, and c without explicit data clauses
        #pragma acc kernels
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                c[x] = c[x] * 2;
            }
        }
    }

    // Checking the results
    for (int x = 0; x < n; ++x) {
        if (fabs(c[x] - 2 * (a[x] + b[x])) > PRECISION) {
            err += 1;
        }
    }

    free(a);
    free(b);
    free(c);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_reference_counters();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}