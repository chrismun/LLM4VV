#include "acc_testsuite.h"
#ifndef T1
// T1: declare directive, V:2.7-3.3
int test1() {
    int err = 0;
    int a = 10;

    #pragma acc declare copyin(a)
    {
        // Use "a" here
        int b = a * 2;
        if (b != 20) {
            err = 1;
        }
    } // End of declare region

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