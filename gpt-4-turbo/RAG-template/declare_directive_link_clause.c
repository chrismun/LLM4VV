#include "acc_testsuite.h"
#ifndef T1
// T1:{feature},V:2.7-3.3

int global_var = 0; // Global variable to be linked in the accelerated region.

#pragma acc declare link(global_var)

int test1(){
    int err = 0;
    srand(SEED);
    
    int original_value = global_var; // Store original global variable value.
    int new_value = rand(); // Generate a new value to update the global variable with.
    
    // Ensure global_var isn't zero to avoid false positives if new_value is 0.
    if (new_value == 0) {
        new_value = 1;
    }

    // Accelerated region where global_var is linked and modified.
#pragma acc parallel
    {
#pragma acc loop
        for (int i = 0; i < 1; ++i) {
            global_var = new_value;
        }
    }
    
    // Error checking: Verify that global_var has been correctly modified.
    if (global_var != new_value) {
        err++;
    }
    
    // Restore original value to ensure isolated test cases.
    global_var = original_value;

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
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