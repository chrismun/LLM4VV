#include <stdio.h>
#include <stdlib.h>

// Define a SEED for reproducibility
#define SEED 12345
// Define the number of times the test should be run
#define NUM_TEST_CALLS 100

// Test T1: serial construct, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    // Initialize data for testing
    int testData = rand() % 100; // Generate a random number
    int resultData = 0; // To store result

    // Using OpenACC serial construct to operate on the testData
    #pragma acc serial copyin(testData) copyout(resultData)
    {
        resultData = testData + 1; // Simple operation to check if executed serially
    }

    // Check if the operation inside the serial construct was performed correctly
    if (resultData != testData + 1) {
        err = 1; // Error occurred, testData was not incremented as expected
    }
    
    return err;
}

int main(){
    int failcode = 0; // Initialize failcode to 0
    int failed = 0; // To keep track of test failures
    
    // Calling test1() NUM_TEST_CALLS times
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    
    // Check if there were any failures
    if (failed != 0){
        failcode = failcode | (1 << 0); // Update failcode if test1 failed
    }
    
    return failcode; // Return failcode, 0 if passed, nonzero if failed
}