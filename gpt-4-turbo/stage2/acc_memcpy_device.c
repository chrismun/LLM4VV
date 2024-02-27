#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>
#include <string.h> // For memcmp

// Assuming acc_testsuite.h defines these. Adjust as per actual implementation.
#define SEED 12345
#define NUM_TEST_CALLS 1

#ifndef T1
//T1:acc_memcpy_device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int dataSize = 1024; // size of data to be copied in bytes
    int *hostData = (int*)malloc(dataSize); // Host data for initialization & verification
    if(hostData == NULL) {
        printf("Memory allocation failed on host.\n");
        return 1;
    }

    // Initialize host data
    for(int i = 0; i < dataSize / sizeof(int); ++i) {
        hostData[i] = rand();
    }

    // Allocate and initialize device memory
    int *deviceSrc = (int*)acc_malloc(dataSize);
    int *deviceDest = (int*)acc_malloc(dataSize);
    if(deviceSrc == NULL || deviceDest == NULL) {
        printf("Device memory allocation failed.\n");
        free(hostData);
        return 1;
    }

    // Ensure we're in an OpenACC data region
    #pragma acc enter data copyin(hostData[0:dataSize / sizeof(int)])
    #pragma acc parallel present(hostData[0:dataSize / sizeof(int)])
    {
        acc_memcpy_device(deviceSrc, hostData, dataSize); // Copy from host to device (src)
    }
    #pragma acc exit data delete(hostData[0:dataSize / sizeof(int)])

    // Perform the device-to-device copy
    acc_memcpy_device(deviceDest, deviceSrc, dataSize); 

    // Copy back the result to the host for verification
    #pragma acc enter data create(hostData[0:dataSize / sizeof(int)])
    #pragma acc parallel present(hostData[0:dataSize / sizeof(int)])
    {
        acc_memcpy_device(hostData, deviceDest, dataSize); // Copy from device (dest) to host
    }
    #pragma acc exit data delete(hostData[0:dataSize / sizeof(int)])

    // Verification
    for(int i = 0; i < dataSize / sizeof(int); ++i) {
        if (hostData[i] != rand()) {
            printf("Mismatch found at position %d\n", i);
            err = 1;
            break;
        }
    }

    // Cleanup
    acc_free(deviceSrc);
    acc_free(deviceDest);
    free(hostData);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    failed = test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    if(failcode == 0) {
        printf("Test passed.\n");
    } else {
        printf("Test failed.\n");
    }
    return failcode;
}