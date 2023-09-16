#include "acc_testsuite.h"

#ifndef T1
// T1: loop construct independent clause, V: 2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    int n = 10;
    int a[n], b[n], c[n];

    for (int i = 0; i < n; i++) {
        a[i] = rand() % n;
        b[i] = rand() % n;
        c[i] = 0;
    }

    #pragma acc kernels loop independent
    for (int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }

    for (int i = 0; i < n; i++) {
        if (c[i] != a[i] + b[i])
            err = 1;
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
        failed += test1();
    }
    if (failed != 0) {
        failcode |= (1 << 0);
    }
#endif

    return failcode;
}