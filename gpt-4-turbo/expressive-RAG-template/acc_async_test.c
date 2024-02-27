#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 5
#endif

// T1:acc_async_test,V:2.7-3.3
int test_acc_async_test() {
    int err = 0;
    srand(SEED);

    // Initialize data and variables
    const int size = 1024;
    double *hostArray = (double*)malloc(size * sizeof(double));
    double *deviceArray;
    int asyncId = rand() % 100; // Generate a random async ID for testing

    // Setup for data on the device
#pragma acc enter data copyin(hostArray[0:size]) async(asyncId)
    
    // Perform a simple operation on the data asynchronously
#pragma acc parallel loop async(asyncId)
    for (int i = 0; i < size; ++i) {
        hostArray[i] = i * 1.0;
    }
    
    // Test if the asynchronous operation has completed
    if (!acc_async_test(asyncId)) {
        printf("Asynchronous operation on ID %d is still running.\n", asyncId);
        err++;
    } else {
        printf("Asynchronous operation on ID %d completed. (This is unexpected before explicit wait)\n", asyncId);
        err++;
    }

    // Ensure the operation is complete before further checks
#pragma acc wait(asyncId)
    
    if (!acc_async_test(asyncId)) {
        printf("Asynchronous operation on ID %d still running after wait. (Unexpected)\n", asyncId);
        err++;
    } else {
        printf("Asynchronous operation on ID %d has completed successfully.\n", asyncId);
    }

    // Cleanup
#pragma acc exit data delete(hostArray[0:size])
    free(hostArray);

    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_acc_async_test();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
    return failcode;
}