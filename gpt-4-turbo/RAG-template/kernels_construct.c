#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
// T1:{kernels_construct},V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    const int n = 100;
    float *a, *b, *c;

    // Allocate memory
    a = (float *)malloc(n * sizeof(float));
    b = (float *)malloc(n * sizeof(float));
    c = (float *)malloc(n * sizeof(float));

    // Initialize arrays
    for (int i = 0; i < n; i++) {
        a[i] = rand() / (float)RAND_MAX;
        b[i] = rand() / (float)RAND_MAX;
        c[i] = 0.0f;
    }

    // Compute vector addition in an OpenACC kernels region
    #pragma acc kernels copyin(a[0:n], b[0:n]) copyout(c[0:n])
    for (int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }

    // Verify the result
    for (int i = 0; i < n; i++) {
        if (abs(c[i] - (a[i] + b[i])) > 1e-5) {
            err++;
        }
    }

    // Clean up
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