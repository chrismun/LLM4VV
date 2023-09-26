#include "acc_testsuite.h"

#ifndef T1
// T1: runtime, data, executable-data, construct-independent, v:2.0-2.7
int test1() {
    int err = 0;
    srand(SEED);

    #pragma acc data detach
    {
        // Code to be executed in parallel
        // ...

        // Verify the correctness of the detached data
        if () {
            err = 1;
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