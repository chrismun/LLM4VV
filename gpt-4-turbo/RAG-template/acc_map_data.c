#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>
#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int dataSize = 1024; // Size of data buffer
    int* hostData = (int*) malloc(sizeof(int) * dataSize); // Allocate host memory
    int* deviceData = (int*) acc_malloc(sizeof(int) * dataSize); // Allocate device memory

    if (hostData == NULL || deviceData == NULL) {
        fprintf(stderr, "Memory allocation error.\n");
        exit(1);
    }

    // Initialize host data
    for(int i = 0; i < dataSize; ++i) {
        hostData[i] = rand() % 100; // Random data
    }

    // Map host data to device data
    acc_map_data(hostData, deviceData, sizeof(int) * dataSize);

    // Verify errors are not set
    if(acc_get_device_type() != acc_device_none) {
        if (acc_get_last_data(runtime) == NULL && acc_get_last_data(argument) == NULL) {
            err = 1;  // Expected to have a valid mapping
        }
    }

    // Example kernel that uses the mapped data
    #pragma acc parallel loop present(hostData[0:dataSize])
    for(int i = 0; i < dataSize; ++i) {
        hostData[i] += 1; // Increment each element by 1
    }

    // Unmap after use
    acc_unmap_data(hostData);

    // Verification
    for(int i = 0; i < dataSize; ++i) {
        if (hostData[i] != (rand() % 100) + 1) {
            err = 1; // Data should have been incremented by 1
            break;
        }
    }

    free(hostData);
    acc_free(deviceData);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}