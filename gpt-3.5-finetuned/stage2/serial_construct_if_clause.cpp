#include "acc_testsuite.h"
#ifndef T1
//T1:serial,V:3.0-3.2
int test1() {
    int err = 0;
    srand(SEED);

#pragma acc serial if(false)
    {
        for (int x = 0; x < n; ++x) {
            if (a[x] != 0.0) {
                err += 1;
            }
        }
    }

    return err;
}

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