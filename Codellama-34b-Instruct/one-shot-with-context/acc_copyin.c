#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 10
#define SEED 12345
#define PRECISION 0.00001

int main() {
    int failcode = 0;
    int failed;

    // Test acc_copyin
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
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
                failed++;
            }
        }

        free(a);
        free(b);
    }

    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    // Test acc_create
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        real_t *a = (real_t *)malloc(n * sizeof(real_t));
        real_t *b = (real_t *)malloc(n * sizeof(real_t));

        for (int i = 0; i < n; ++i) {
            a[i] = rand() / (real_t)(RAND_MAX / 10);
            b[i] = 0;
        }

        #pragma acc data create(a[0:n])
        {
            #pragma acc kernels create(b[0:n])
            {
                #pragma acc loop
                for (int i = 0; i < n; ++i) {
                    b[i] = a[i];
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            if (fabs(b[i] - a[i]) > PRECISION) {
                failed++;
            }
        }

        free(a);
        free(b);
    }

    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }

    return failcode;
}