#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 10
#define SEED 123456789
#define PRECISION 0.00001

int test1(int n, int num_workers) {
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc kernels num_workers(num_workers) copyout(b[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x) {
                b[x] = a[x];
            }
        }
    }

    for (int x = 0; x < n; ++x) {
        if (fabs(b[x] - a[x]) > PRECISION) {
            err += 1;
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1(100, 4);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}