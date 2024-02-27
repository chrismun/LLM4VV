#include <stdio.h>
#include <stdlib.h>
#include <openacc.h> // Ensure OpenACC support

#define SEED 12345
#define NUM_TEST_CALLS 10

// Global variable for testing the link clause
int global_var = 0;

// Using OpenACC declare directive with link clause for global_var
#pragma acc declare link(global_var)

// Test function
#ifndef T1
// T1:declare directive link clause,V:2.7-3.3
int test1(){
    int err = 0;
    int original_value = global_var; // Store original value of global_var
    int new_value = rand() % 100; // Generate a random new value
    
    // Modify global_var on the device
    #pragma acc parallel
    {
        global_var = new_value;
    }

    // Check if global_var was correctly updated
    if (global_var != new_value){
        err = 1; // Error if global_var wasn't updated correctly
    } else {
        global_var = original_value; // Reset global_var to original value
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    srand(SEED);
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}