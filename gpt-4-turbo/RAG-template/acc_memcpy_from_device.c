#include "acc_testsuite.h"
#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const size_t dataSize = 1024; // Number of bytes to copy
    char *hostData = (char*) malloc(dataSize * sizeof(char));
    char *deviceData;

    // Initialize host data
    for(size_t i = 0; i < dataSize; ++i) {
        hostData[i] = rand() % 256;
    }

    // Allocate memory on the device and copy data from host to device
    deviceData = (char*) acc_malloc(dataSize * sizeof(char));
    acc_memcpy_to_device(deviceData, hostData, dataSize);

    // Modify the data on the device to test the copy back
    #pragma acc parallel loop deviceptr(deviceData)
    for(size_t i = 0; i < dataSize; ++i) {
        deviceData[i] += 1; // Simple operation to modify the data
    }

    // Copy data back from device to host
    acc_memcpy_from_device(hostData, deviceData, dataSize);

    // Verify the copied data
    for(size_t i = 0; i < dataSize; ++i) {
        if (hostData[i] != (char)((rand() % 256) + 1)) { // The original data +1
            err++;
        }
    }

    // Clean up
    free(hostData);
    acc_free(deviceData);

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
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}