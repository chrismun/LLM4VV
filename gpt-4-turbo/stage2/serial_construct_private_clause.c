#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Define constants for the test suite
#define SEED 12345
#define NUM_TEST_CALLS 10

// Test for OpenACC serial construct with a private clause
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize a variable to test with
    int original_value = rand() % 100;  // Random value
    int test_value = original_value;

    // OpenACC serial region where test_value is private
    #pragma acc serial private(test_value)
    {
        // Modify the private test_value within the region
        test_value += 5;
    }
    // After the serial region, test_value should not have changed as it was private
    if (test_value != original_value) {
        // If test_value has changed, an error occurred
        err++;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;

    // Run the test multiple times to check consistency
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }

    // If any of the tests failed, adjust the failcode
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    // Return failcode, 0 if success, nonzero if failed
    return failcode;
}