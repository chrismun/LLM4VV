#include "acc_testsuite.h"
#ifndef T1
// T1: compute construct private clause, V: 2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    // Declare a private variable
    int private_var = 0;

    #pragma acc data copy(private_var)
    {
        #pragma acc parallel loop private(private_var)
        for (int i = 0; i < N; ++i) {
            private_var = i;  // Update private variable
        }
    }

    // Validate if the private variable holds the expected value
    int expected_val = N - 1;
    if (private_var != expected_val) {
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