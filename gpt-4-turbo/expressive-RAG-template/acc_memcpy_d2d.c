#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h" // Note: This is a hypothetical include for context.

#ifndef T1
//T1:acc_memcpy_d2d,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int dataSize = 1024; // Size of the array
    float *srcArray, *destArray;

    // Allocate memory on the device for source and destination arrays
    srcArray = (float*) acc_malloc(dataSize * sizeof(float));
    destArray = (float*) acc_malloc(dataSize * sizeof(float));

    // Check for successful memory allocation on device
    if (srcArray == NULL || destArray == NULL) {
        printf("Memory allocation on device failed.\n");
        return 1; // Memory allocation error
    }

    // Initialize source array with random numbers
    #pragma acc parallel loop present(srcArray)
    for (int i = 0; i < dataSize; i++) {
        srcArray[i] = rand() / (float)RAND_MAX;
    }

    // Get current device number as we're working on the same device
    int currentDevice = acc_get_device_num(acc_get_device_type());

    // Perform device to device copy
    acc_memcpy_d2d(destArray, srcArray, dataSize * sizeof(float), currentDevice, currentDevice);

    // Verify the copy by comparing arrays
    #pragma acc parallel loop present(srcArray, destArray) reduction(+:err)
    for (int i = 0; i < dataSize; i++) {
        if (srcArray[i] != destArray[i]) {
            err += 1; // Increment error if values don't match
        }
    }

    // Free allocated memory
    acc_free(srcArray);
    acc_free(destArray);

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
        printf("Test1 failed.\n");
        failcode = failcode + (1 << 0);
    }
    else {
        printf("Test1 passed.\n");
    }
#endif
    return failcode;
}