#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.0001

int test_acc_memcpy_device(int n) {
    int err = 0;
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc kernels copyout(b[0:n])
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

    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test_acc_memcpy_device(100);
        if (failed != 0) {
            failcode = failcode + (1 << 0);
        }
    }

    return failcode;
}