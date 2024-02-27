#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#define SEED 12345
#define NUM_ELEMENTS 1024
#define NUM_TEST_CALLS 10

// Assuming this is defined in "acc_testsuite.h" or similar
// For the purposes of this example, we simulate these definitions
#define T1 // Predefine T1 to remove conditional compilation related to this test

int test1(){
    int err = 0;
    srand(SEED);

    int *arr_host = (int*) malloc(NUM_ELEMENTS * sizeof(int));
    // Populate array with known values
    for(int i = 0; i < NUM_ELEMENTS; i++){
        arr_host[i] = rand() % 1000; // Fill with random data as per SEED
    }

    // Copying data to device and modifying it there
    #pragma acc data copy(arr_host[0:NUM_ELEMENTS])
    {
        #pragma acc parallel loop
        for(int i = 0; i < NUM_ELEMENTS; i++){
            arr_host[i] += 1; // Simple operation to modify values in device memory
        }

        // Reflect changes back to host memory
        #pragma acc update self(arr_host[0:NUM_ELEMENTS])
    }

    // Verify that the changes are reflected back correctly
    for(int i = 0; i < NUM_ELEMENTS; i++){
        if(arr_host[i] != (rand() % 1000) + 1){ // Checks if the initial value +1 doesn't match
            err++;
            break;
        }
    }

    free(arr_host);
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    if(failcode == 0) {
        printf("Test Passed\n");
    } else {
        printf("Test Failed\n");
    }
    return failcode;
}