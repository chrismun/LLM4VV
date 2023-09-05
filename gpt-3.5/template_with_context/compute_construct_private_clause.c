#include "acc_testsuite.h"

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    srand(SEED);

    int private_var = 0;
    #pragma acc parallel private(private_var)
    {
        private_var = 1;
    }

    if (private_var != 0) {
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
        failcode += (1 << 0);
    }
#endif

    return failcode;
}