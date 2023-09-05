#include "acc_testsuite.h"

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    srand(SEED);

    #pragma acc parallel loop collapse(2)
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            // Perform computation
            int val = i + j;
            // Check if computation is correct
            if (val != i + j) {
                err = 1;
            }
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
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}