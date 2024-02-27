#include <openacc.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// Seed for random number generation -- Ensure that SEED is defined
#ifndef SEED
#define SEED 42
#endif

// Number of test calls -- Ensure that NUM_TEST_CALLS is defined
#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// Test to check acc_async_test functionality
int test1(){
    int err = 0;
    const int size = 1024;
    float *hostArray = (float*)malloc(size * sizeof(float));
    float *deviceArray;

    // Initialize host array with random data
    srand(SEED);
    for(int i = 0; i < size; ++i){
        hostArray[i] = rand() / (float)RAND_MAX;
    }

    int async_tag = 1; // Label for async operation

    // Begin an OpenACC data region, with async copy to device
    #pragma acc data copyin(hostArray[0:size]) create(deviceArray[0:size])
    {
        #pragma acc parallel async(async_tag)
        {
            deviceArray = hostArray; // Simulated data processing
        }

        // Use acc_async_test to check if the async operation has completed
        // The operation is assumed incomplete, so it should return false (0)
        if(acc_async_test(async_tag)){
            printf("Unexpected early completion of the async operation.\n");
            err++;
        }

        // Wait for the completion of the operation
        #pragma acc wait(async_tag)

        // After explicit wait, acc_async_test should now return true (1)
        if(!acc_async_test(async_tag)){
            printf("Async operation did not complete as expected.\n");
            err++;
        }
    }
    
    free(hostArray);

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }

    if (failed != 0){
        failcode += (1 << 0);
    }
    if(failcode) {
        printf("Test FAILED with code %d.\n", failcode);
    } else {
        printf("All tests passed successfully.\n");
    }
    return failcode;
}