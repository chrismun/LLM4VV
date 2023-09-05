#include "acc_testsuite.h"

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    srand(SEED);

    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));
    int *c = (int*)malloc(N * sizeof(int));
    int *d = (int*)malloc(N * sizeof(int));

    // Initialize the input arrays
    init_array(N, a);
    init_array(N, b);

    #pragma acc data copyin(a[0:N], b[0:N]) copyout(c[0:N]) create(d[0:N])
    {
        // Perform computation in parallel asynchronously
        #pragma acc parallel loop async
        for (int i = 0; i < N; ++i) {
            d[i] = a[i] + b[i];
        }

        // Perform computation in parallel
        #pragma acc parallel loop
        for (int j = 0; j < N; ++j) {
            c[j] = d[j] * d[j];
        }

        // Wait for all previous asynchronous tasks to complete
        #pragma acc waitall
    }

    // Validate the result
    if (!validate(N, c)) {
        err = 1;
    }

    free(a);
    free(b);
    free(c);
    free(d);

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