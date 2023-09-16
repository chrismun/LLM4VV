#include "acc_testsuite.h"
#ifndef T1
// T1: acc init, V: 2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    #pragma acc parallel loop
    for (int i = 0; i < LENGTH; i++) {
        data[i] = 0; // Initialize data array elements to 0
    }

    #pragma acc update self(data[0:LENGTH])

    for (int i = 0; i < LENGTH; i++) {
        if (data[i] != 0) {
            err = 1; // Check if data array elements are not 0
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
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}