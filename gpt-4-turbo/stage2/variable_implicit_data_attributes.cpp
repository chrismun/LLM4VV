#include <iostream>
#include <stdlib.h> // For rand(), srand()
#include <openacc.h> // Required for OpenACC 

constexpr int SEED = 1234; // Seed for srand()

// Define a macro as a simple approximation for performing repeated test calls
#define NUM_TEST_CALLS 10

#ifndef T1
// T1: variable implicit data attributes, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    int testData = rand() % 100; // Sample data to work with
    
    // The following OpenACC region tries to modify testData implicitly
#pragma acc parallel copy(testData)
    {
        testData += 1; // An implicit 'copy' clause should apply here for scalar variable
    }

    // Verifying the testData is modified as expected.
    if (testData == (rand() % 100) + 1) {
        std::cout << "Data modified as expected with implicit 'copy' attribute.\n";
    } else {
        std::cout << "Unexpected behavior with implicit data attribute handling.\n";
        err = 1; // Setting err to non-zero value indicates the test failed
    }

    return err;
}
#endif

int main() {
    int failcode = 0; // Initialize failcode to 0, representing success.
    int failed = 0; // Variable to keep track of failures
    
#ifndef T1
    srand(SEED); // Ensuring rand() is initialized with the same seed before every test1 call
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test1();
    }
    if (failed != 0) {
        std::cout << "Test finished with errors.\n";
        failcode += (1 << 0); // Adjust failcode accordingly to indicate which test failed
    } else {
        std::cout << "All tests passed successfully.\n";
    }
#endif

    return failcode; // Return failcode (0 for success, non-zero for any errors)
}