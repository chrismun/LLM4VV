#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

//T1:host_data construct if clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int hostVar = 0;
    int* devicePtr;
    
    // Allocate device memory
    devicePtr = (int*) acc_malloc(sizeof(int));
    *devicePtr = 0; // Initialize device memory

    // Test scenario where if condition evaluates to true
    int conditionTrue = 1;
    #pragma acc host_data if(conditionTrue) use_device(devicePtr)
    {
        *devicePtr = 5; // Modify using device pointer, should reflect because condition is true
    }

    // Copy back to host to check
    acc_memcpy_from_device(&hostVar, devicePtr, sizeof(int));
    if (hostVar != 5) {
        err++;
    }

    // Reset for next test
    hostVar = 0;
    *devicePtr = 0;

    // Test scenario where if condition evaluates to false
    int conditionFalse = 0;
    #pragma acc host_data if(conditionFalse) use_device(devicePtr)
    {
        *devicePtr = 10; // Attempt to modify using device pointer, should not reflect because condition is false
    }

    // Copy back to host to check
    acc_memcpy_from_device(&hostVar, devicePtr, sizeof(int));
    if (hostVar != 0) {
        err++;
    }

    // Free the allocated memory
    acc_free(devicePtr);

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
    printf("Test %s\n", failcode == 0 ? "passed" : "failed");
    return failcode;
}