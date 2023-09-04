#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.001

int test_routine(int n, real_t *a, real_t *b) {
    int err = 0;
    #pragma acc routine(test_routine)
    {
        #pragma acc kernels
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                b[x] = a[x];
            }
        }
    }
    return err;
}

int main() {
    int failcode = 0;
    int failed;
    real_t *a, *b;
    int n = 100;

    a = (real_t *)malloc(n * sizeof(real_t));
    b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    failed = test_routine(n, a, b);

    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    free(a);
    free(b);

    return failcode;
}