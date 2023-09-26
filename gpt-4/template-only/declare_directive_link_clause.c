#include "acc_testsuite.h"

// Test OpenACC declare directive link clause
int test1() {
    int err = 0;
    srand(SEED);

    int a = 0, b = 5, c = 10;

    #pragma acc declare link(a, b, c)

    #pragma acc parallel num_gangs(1) vector_length(1)
    {
        a = b + c; // This should execute without errors, if link clause is properly implemented
    }

    // Check if the computation was executed correctly on the device
    if(a != (b + c)) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}