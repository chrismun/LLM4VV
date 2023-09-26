#include "acc_testsuite.h"
#ifndef T1
// T1: runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    srand(SEED);
    int a[10], b[10], c[10];
    int i, j;

    for (i = 0; i < 10; i++) {
        a[i] = rand() % 10;
        b[i] = rand() % 10;
    }

#pragma acc kernels
    for (i = 0; i < 10; i++) {
#pragma acc loop
        for (j = 0; j < 10; j++) {
            c[i] += a[i] * b[i];
        }
    }

#pragma acc wait any

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