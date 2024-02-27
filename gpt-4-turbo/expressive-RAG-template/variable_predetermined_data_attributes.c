#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// A simple function to check errors.
int checkForErrors(int *data, int size, int expected) {
    for (int i = 0; i < size; ++i) {
        if (data[i] != expected) {
            return 1; // Error found
        }
    }
    return 0;
}

// Test for OpenACC loop variable predetermination
int test_loop_variable_private_attribute(){
    int err = 0;
    const int size = 100;
    int data[size];

    // Initialize data array
    for (int i = 0; i < size; i++) {
        data[i] = 0;
    }

    // Performing parallel modification of the data array
    #pragma acc parallel loop
    for (int i = 0; i < size; i++) {
        int temp = i * 2; // temp is the loop variable expected to be private to each iteration
        data[i] = temp;
    }

    // Check if data array has the expected results
    err = checkForErrors(data, size, -1); // -1 is a dummy value as we do not expect this condition to be hit.
    for (int i = 0; i < size; i++) {
        if (data[i] != i * 2) { // Each element should have been multiplied by 2
            err = 1; // The error shows that loop variables were not successfully kept private
            break;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_loop_variable_private_attribute();
    }
    if (failed != 0){
        failcode = 1;
    }
    if (failcode == 0) {
        printf("Test PASSED.\n");
    } else {
        printf("Test FAILED.\n");
    }
    return failcode;
}