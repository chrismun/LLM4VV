#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.0001

int main() {
    int failcode = 0;
    int failed;

    // Test 1: Data Specification in Data Clauses
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        int err = 0;
        srand(SEED);
        real_t *a = (real_t *)malloc(n * sizeof(real_t));
        real_t *b = (real_t *)malloc(n * sizeof(real_t));

        for (int i = 0; i < n; ++i) {
            a[i] = rand() / (real_t)(RAND_MAX / 10);
            b[i] = 0;
        }

        #pragma acc data copyin(a[0:n])
        {
            #pragma acc kernels copyout(b[0:n])
            {
                #pragma acc loop
                for (int i = 0; i < n; ++i) {
                    b[i] = a[i];
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            if (fabs(b[i] - a[i]) > PRECISION) {
                err += 1;
            }
        }

        if (err > 0) {
            failed += 1;
        }
    }

    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}