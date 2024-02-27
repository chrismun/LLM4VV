#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
// T1:serial construct default clause, V:2.7-3.3
int test1(){
    int err = 0;
    srand(42); // Fixed seed for reproducibility

    int test_var = rand(); // Initialize a variable outside the OpenACC region
    int original_value = test_var; // Store its original value for comparison

    // Apply a simple operation in an OpenACC serial construct without specifying the default clause
    #pragma acc serial
    {
        test_var += 1; // Modify the variable inside the OpenACC region
    }

    // Check if the modification inside the OpenACC region affected the variable outside
    // Given that the default behavior typically shares variables between host and device,
    // we check if the change is visible here.
    // If the variable was private to the region (incorrectly due to some compiler issue), this check will fail.
    if(test_var != original_value + 1){
        err += 1; // Error if the variable was not correctly shared (or any unexpected behavior)
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
    const int NUM_TEST_CALLS = 10;

#ifndef T1
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