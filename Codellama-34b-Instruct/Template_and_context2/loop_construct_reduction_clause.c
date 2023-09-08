#include "acc_testsuite.h"

#ifndef T1
// T1: loop construct reduction clause, V: 2.7-3.3
int test1() {
    int err = 0;

    // Initialize variables
    int x = 0;
    int y = 0;
    int z = 0;

    // Set up the loop
    #pragma acc parallel loop reduction(+:x, y, z)
    for (int i = 0; i < 10; ++i) {
        x += 1;
        y += 2;
        z += 3;
    }

    // Check the results
    if (x != 10 || y != 20 || z != 30) {
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
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}