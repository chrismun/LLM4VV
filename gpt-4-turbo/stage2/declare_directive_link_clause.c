#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
// T1:declare directive link clause,V:2.7-3.3

// Global variable to test link clause with
int global_test_var = 10;

// Declare link clause for the global variable
#pragma acc declare link(global_test_var)

int test1(){
    int err = 0;
    srand(42);

    // Original value of the global variable
    int original_value = global_test_var;
    int update_value = rand() % 100; // Random value to add

    // Modify global variable in a parallel region on the device
    #pragma acc parallel
    {
        #pragma acc loop
        for(int i = 0; i < 1; i++){
            global_test_var += update_value;
        }
    }

    // Update host variable by copying data from the device
    #pragma acc update self(global_test_var)

    if (global_test_var != original_value + update_value) {
        printf("Test failed: Expected %d, got %d\n", original_value + update_value, global_test_var);
        err++;
    } else {
        printf("Test passed: Global variable updated correctly.\n");
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
#ifndef T1
    if (test1() != 0){
        failcode = 1;
    }
#endif
    if (failcode == 0) {
        printf("All tests passed.\n");
    } else {
        printf("Some tests failed.\n");
    }
    return failcode;
}