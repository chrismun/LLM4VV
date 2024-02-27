#include "acc_testsuite.h"
#ifndef T2
// T2:kernels,loop,worker,V:1.0-2.7
int test2() {
    int err = 0;
    const int workers = 4; // Assuming we target 4 workers for this test
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:n])
    {
        #pragma acc parallel copyout(b[0:n]) num_workers(workers)
        {
            #pragma acc loop worker
            for (int x = 0; x < n; ++x) {
                b[x] = a[x] * 2; // Simple operation to ensure work is done
            }
        }
    }

    // Verification of the operation to ensure all elements were processed
    for (int x = 0; x < n; ++x) {
        if (fabs(b[x] - (a[x] * 2)) > PRECISION) {
            err += 1;
        }
    }

    free(a);
    free(b);
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test2();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }
#endif

    return failcode;
}