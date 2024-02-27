#include "acc_testsuite.h"
#ifndef T1
// T1: parallel, loop, seq, V:1.0-2.7
int test1() {
    int err = 0;
    srand(SEED);
    real_t* a = (real_t*)malloc(n * sizeof(real_t));
    real_t* b = (real_t*)malloc(n * sizeof(real_t));

    // Initialize arrays with random data
    for (int x = 0; x < n; ++x) {
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    // Parallel region to demonstrate seq clause
    #pragma acc parallel copyin(a[0:n]) copyout(b[0:n])
    {
        // Using seq clause to ensure the loop runs sequentially within the parallel region
        #pragma acc loop seq
        for (int x = 0; x < n; ++x) {
            b[x] = a[x];
        }
    }

    // Validate correct data transfer and sequential operation
    for (int x = 0; x < n; ++x) {
        if (fabs(b[x] - a[x]) > PRECISION) {
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

#ifndef T1
    failed = test1();
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}