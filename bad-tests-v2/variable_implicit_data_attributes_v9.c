#include "acc_testsuite.h"
#ifndef T1
// T1: runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;
    srand(SEED);

    #pragma acc data copy(err)
    {
        #pragma acc parallel loop
        for (int i = 0; i < 100; i++) {
            if (i % 2 == 0) {
                err += i;
            } else {
                err -= i;
            }
        }
    }

    return err != 0;
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