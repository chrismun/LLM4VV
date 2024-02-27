#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

int test_attach_clause() {
    int err = 0;
    const int size = 1024;
    int* hostArray = (int*)malloc(sizeof(int) * size);
    
    // Initialize array
    for(int i = 0; i < size; ++i) {
        hostArray[i] = rand() % 100; // Populate with some data.
    }
    
    // Use OpenACC to attach the array to the device.
    #pragma acc enter data copyin(hostArray[0:size])
    
    // Modify the data on the device
    #pragma acc parallel loop present(hostArray[0:size])
    for(int i = 0; i < size; ++i) {
        hostArray[i] += 1; // Increment each element to test data transfer.
    }
    
    // Detect and detach the data.
    #pragma acc exit data copyout(hostArray[0:size])

    // Check for correctness
    for(int i = 0; i < size; ++i) {
        if(hostArray[i] % 100 == 0) { // Assuming original numbers were <100, they should now not be evenly divisible by 100.
            err = 1;
            break;
        }
    }
    
    free(hostArray);
    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_attach_clause();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
    printf("Test %s\n", failcode == 0 ? "PASSED" : "FAILED");
    return failcode;
}