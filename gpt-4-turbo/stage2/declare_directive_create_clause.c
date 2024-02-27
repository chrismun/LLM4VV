#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// You might need to implement or include a header file named 'acc_testsuite.h' if you are working within a larger testsuite context.
// For the purpose of this example, we'll assume it contains definitions for SEED, NUM_TEST_CALLS, and potentially other utility functions or macros for testing.

#ifndef T1
// T1: declare directive create clause, V: 2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    // Variable to test with OpenACC declare directive
    int test_var = rand(); // Initialize with a random value

    // Using OpenACC declare directive to specify test_var should be created on the device
    #pragma acc declare create(test_var)

    // Performing a parallel operation that uses test_var. The goal is to add 1 to test_var on the device to verify its creation and accessibility.
    #pragma acc parallel copy(test_var)
    {
        test_var += 1;
    }

    // Verification:
    // After adding 1 to the original value of test_var on the device, we need to check if this operation was successful.
    // If successful, the operation indicates that test_var was indeed created on the device and is accessible.
    // Since we initialized test_var with rand() and added 1 to it in the device, we now subtract 1 to validate.
    if (test_var - 1 == rand()) {
        // The test passes if test_var - 1 equals the initial random value, demonstrating that test_var was correctly manipulated on the device.
        err = 0;
    } else {
        // If the test fails, an error is recorded.
        err = 1;
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
#endif
    return failcode;
}