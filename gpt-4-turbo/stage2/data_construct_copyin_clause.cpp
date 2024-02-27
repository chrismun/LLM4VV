#include <iostream>
#include <cstdlib>
#include <openacc.h>

// Seed for randomness to ensure repeatability
#define SEED 42
// Number of iterations to verify the copyin operation effectively
#define NUM_TEST_CALLS 10

int test_copyin(){
    int err = 0;
    int host_var = 10; // Initial value of the variable to be copied in

    // Modify the variable to verify if the modification is reflected in the device
    host_var += 5;

    // Using OpenACC parallel region with copyin clause
#pragma acc parallel copyin(host_var)
    {
        // Since we are only testing the copyin functionality,
        // No modification or computation is done on the device with host_var
#pragma acc loop
        for(int i = 0; i < 1; ++i){
            if(host_var != 15){ // Check if the copied value is as expected
                err = 1; // Error if the value is not what we modified it to be
            }
        }
    }
    return err;
}

int main(){
    srand(SEED);
    int failcode = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        if(test_copyin() != 0){
            failcode = 1; // Set failcode to 1 if any test fails
            break; // Exit the loop if a failure is found
        }
    }

    if (failcode != 0){
        std::cout << "Test failed: OpenACC copyin clause not working as expected." << std::endl;
    } else {
        std::cout << "All tests passed: OpenACC copyin clause is working as expected." << std::endl;
    }

    return failcode;
}