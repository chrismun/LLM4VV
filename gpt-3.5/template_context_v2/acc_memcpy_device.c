#include "acc_testsuite.h"
#ifndef T1
// T1: acc_memcpy_device, V: 2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    int n = 100;
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    int *c = (int *)malloc(n * sizeof(int));

    // Initialize arrays a and b
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    // Copy arrays a and b to the device
    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        // Perform element-wise addition on the device
        #pragma acc parallel loop gang worker vector
        for (int i = 0; i < n; i++) {
            c[i] = a[i] + b[i];
        }
    }

    // Verify the result
    for (int i = 0; i < n; i++) {
        if (c[i] != a[i] + b[i]) {
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
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}