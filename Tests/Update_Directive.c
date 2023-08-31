#include "acc_testsuite.h"

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    srand(SEED);

    // Initialize the arrays
    int a[N], b[N], c[N];
    for (int i = 0; i < N; i++) {
        a[i] = rand() % 10;
        b[i] = rand() % 10;
        c[i] = 0;
    }

    // Update the arrays using the update directive
    #pragma acc update device(a, b, c)

    // Verify that the arrays have been updated correctly
    for (int i = 0; i < N; i++) {
        if (a[i] != b[i]) {
            err = 1;
            break;
        }
    }

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