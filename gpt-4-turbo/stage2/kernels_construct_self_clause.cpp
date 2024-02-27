#include <iostream>
#include <stdlib.h> // For rand() and srand()
#include <openacc.h> // Necessary for OpenACC API

// Emulating a potential acc_testsuite.h for unified constants and possibly utility functions
// This is a simplified mock-up version.
#ifndef ACC_TESTSUITE_H
#define ACC_TESTSUITE_H
const int SEED = 42;
const int NUM_TEST_CALLS = 10;
#endif

#ifndef T1
// T1:kernels construct self clause, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    
    const int size = 1; // Keeping the test focused on a single element for clarity
    int data[size] = {0}; // Initial data setup
    int original_value = rand(); // Generate a random value for testing
    data[0] = original_value; // Set the value in the array
    
    // The use of the self clause should prevent automatic data copying to/from the GPU
    #pragma acc kernels self(data[0])
    {
        data[0] = data[0] + 1; // Attempt to modify the value, should not affect host data
    }

    // Verify if the modification did not affect the original data
    if (data[0] != original_value) {
        err = 1; // Error if data was modified, indicating possible incorrect self clause behavior
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed = 0;

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