#include "acc_testsuite.h"

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));

    // Initialize arrays
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    // Compute the sum of corresponding elements
    for (int i = 0; i < n; i++) {
        a[i] = a[i] + b[i];
    }

#pragma acc parallel loop present(a, b)
    for (int i = 0; i < n; i++) {
        a[i] = a[i] + b[i];
    }

#pragma acc parallel loop present(a) delete(b)
    for (int i = 0; i < n; i++) {
        a[i] = a[i] + b[i];
    }

    for (int i = 0; i < n; i++) {
        if (a[i] != (b[i] * 2)) {
            err = 1;
            break;
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
    failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }

    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif

    return failcode;
}