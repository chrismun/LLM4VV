#include <iostream>
#include <cstdlib>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Declare a global variable
    int global_var = 0;

    // Declare a link clause
    #pragma acc declare link(global_var)

    // Use the global variable in an accelerator routine
    #pragma acc parallel
    {
        global_var = 1;
    }

    // Check that the global variable has been updated
    if (global_var != 1) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test multiple times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}