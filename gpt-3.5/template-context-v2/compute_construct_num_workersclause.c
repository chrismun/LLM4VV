#include "acc_testsuite.h"

#ifndef T1
// T1: compute construct num_workers clause, V: 2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    #pragma acc parallel num_workers(4)
    {
        if (acc_get_num_workers() != 4) {
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
        failcode += (1 << 0);
    }
#endif

    return failcode;
}