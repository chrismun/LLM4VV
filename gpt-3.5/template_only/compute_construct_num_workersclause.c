#include "acc_testsuite.h"

#ifndef T1
// T1: runtime,data,executable-data,construct-independent,V:2.0-2.7

// Define the problem size
#define N 1000

int test1() {
    int err = 0;

    // Input and output arrays
    float *a = (float *)malloc(N * sizeof(float));
    float *b = (float *)malloc(N * sizeof(float));
    float *c = (float *)malloc(N * sizeof(float));

    // Initialize input arrays
    for (int i = 0; i < N; ++i) {
        a[i] = 1.0f;
        b[i] = 2.0f;
    }

    // Compute c = a + b using OpenACC compute construct with num_workers clause
    #pragma acc data copyin(a[0:N], b[0:N]), copyout(c[0:N])
    {
        #pragma acc parallel loop num_workers(2)
        for (int i = 0; i < N; ++i) {
            c[i] = a[i] + b[i];
        }
    }

    // Verify the result
    for (int i = 0; i < N; ++i) {
        if (c[i] != 3.0f) {
            err = 1;
            break;
        }
    }

    // Free memory
    free(a);
    free(b);
    free(c);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
    
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode |= (1 << 0);
    }
#endif

    return failcode;
}