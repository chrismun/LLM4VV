#include "acc_testsuite.h"
#ifndef T1
// T1: loop construct seq clause, V: 2.7-3.3
int test1() {
    int err = 0;
    int a[10], b[10], c[10];
    srand(SEED);

    // Initialize arrays with random values
    for (int i = 0; i < 10; i++) {
        a[i] = rand() % 100;
        b[i] = rand() % 100;
        c[i] = 0;
    }

    // Perform element-wise addition sequentially
    #pragma acc parallel loop seq
    for (int i = 0; i < 10; i++) {
        c[i] = a[i] + b[i];
    }

    // Verify the correctness of the addition
    for (int i = 0; i < 10; i++) {
        if (c[i] != a[i] + b[i]) {
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
        failed += test1();
    }
    if (failed != 0) {
        failcode |= (1 << 0);
    }
#endif
    return failcode;
}