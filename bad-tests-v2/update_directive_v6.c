#include "acc_testsuite.h"
#ifndef T1
// T1: update directive, V: 2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    int *x = (int *)malloc(N * sizeof(int));
    int *y = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++) {
        x[i] = rand() % N;
        y[i] = 0;
    }

    #pragma acc data copyin(x[0:N]) // Copy input data to device
    #pragma acc kernels
    {
        #pragma acc loop independent
        for (int i = 0; i < N; i++) {
            x[i] = x[i] + 1; // Update array element on device
        }
    }

    #pragma acc host_data use_device(x) // Copy updated data back to host
    {
        for (int i = 0; i < N; i++) {
            if (x[i] != y[i] + 1) {
                err = 1; // Check if device data was correctly updated
                break;
            }
        }
    }

    free(x);
    free(y);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}