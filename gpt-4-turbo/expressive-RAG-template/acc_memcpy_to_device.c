#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
// T1:acc_memcpy_to_device,V:2.7-3.3
int test1(){
    int err = 0; // Error count
    srand(SEED); // Initialize random seed

    // Test data
    const int dataSize = 1024; // Size of the data array
    int *hostData = (int*) malloc(dataSize * sizeof(int)); // Allocate host memory
    int *deviceData = (int*) acc_malloc(dataSize * sizeof(int)); // Allocate device memory

    // Initialize host data
    for(int i = 0; i < dataSize; i++) {
        hostData[i] = rand(); // Fill with random data
    }

    // Perform memcpy from host to device
    acc_memcpy_to_device(deviceData, hostData, dataSize * sizeof(int));

    // Verification array to check data
    int *verificationData = (int*) malloc(dataSize * sizeof(int));

    // Copy back to check if the data has been copied correctly
    acc_memcpy_from_device(verificationData, deviceData, dataSize * sizeof(int));

    // Verify data
    for (int i = 0; i < dataSize; i++) {
        if (hostData[i] != verificationData[i]) {
            err++; // Data mismatch
            break;
        }
    }

    // Cleanup
    free(hostData);
    free(verificationData);
    acc_free(deviceData);

    return err; // 0 if success, nonzero if there was a data mismatch
}
#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    // Since test is deterministic, one call should suffice, but loop for consistency
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0); // Mark test 1 as failed
    }
#endif

    // Return 0 if all tests passed, nonzero if any failed
    return failcode;
}