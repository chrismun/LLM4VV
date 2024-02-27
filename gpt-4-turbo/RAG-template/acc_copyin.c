#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>
#ifndef T1
//T1:runtime,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    
    // Test parameters
    const int dataSize = 1024;
    int* hostData = (int*)malloc(dataSize * sizeof(int));
    int* deviceData;
    int* readBackData = (int*)malloc(dataSize * sizeof(int));
    
    // Initialize host data
    for (int i = 0; i < dataSize; ++i) {
        hostData[i] = rand() % 100;
    }

    // Use acc_copyin to copy data to the device
    #pragma acc enter data copyin(hostData[0:dataSize])
    deviceData = (int*)acc_copyin(hostData, dataSize * sizeof(int));
    #pragma acc exit data copyout(hostData[0:dataSize])
    
    // Copy back the device data to readBackData array for validation
    #pragma acc parallel loop copyout(readBackData[0:dataSize])
    for (int i = 0; i < dataSize; ++i) {
        readBackData[i] = deviceData[i];
    }

    // Validate the data copied back
    for (int i = 0; i < dataSize; ++i) {
        if (readBackData[i] != hostData[i]) {
            printf("Data mismatch at index %d: hostData = %d, readBackData = %d\n", i, hostData[i], readBackData[i]);
            err++;
        }
    }
    
    // Cleanup
    free(hostData);
    free(readBackData);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}