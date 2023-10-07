#include "acc_testsuite.h"

// Test for private clause
int test_private() {
    int err = 0;
    int a[100];
    int b[100];
    srand(SEED);

    for (int i = 0; i < 100; ++i) {
        a[i] = rand();
        b[i] = 0;
    }

    #pragma acc parallel loop private(a)
    for (int i = 0; i < 100; ++i) {
        b[i] = a[i];
    }

    for (int i = 0; i < 100; ++i){
        if (b[i] != a[i]){
            err += 1;
        }
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;

    for (int i = 0; i < NUM_TEST_CALLS; ++i) {
        failed += test_private();
    }

    if (failed != 0) {
        failcode += (1 << 0);
    }

    return failcode;
}