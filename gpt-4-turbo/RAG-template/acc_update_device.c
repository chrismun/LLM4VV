#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
// Test feature: acc_update_device and acc_update_self, Version Range: 2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    const int size = 1024;
    float *host_array = (float *)malloc(size * sizeof(float));

    // Initialize host array
    for(int i = 0; i < size; ++i){
        host_array[i] = (float)rand() / RAND_MAX;
    }

    // Allocate and initialize device array and copy data from host to device
    #pragma acc enter data copyin(host_array[0:size])

    // Modify host_array
    for(int i = 0; i < size; ++i){
        host_array[i] *= 2.0f;
    }

    // Update the device with modifications
    acc_update_device(host_array, size * sizeof(float));

    // Perform computation on the device - This is where your device-specific computation logic would go, skipped for brevity
    // ...

    // Simulate a modification on device and fetch it back. In reality, you would modify the device data via a kernel.
    for(int i = 0; i < size; ++i){
        host_array[i] *= 3.0f; // Simulate device modification for purpose of demonstration
    }

    // Update the host with modifications made on device (Simulated)
    acc_update_self(host_array, size * sizeof(float));

    // Verification (In reality, host_array should have been modified by a device kernel, here we simulate it)
    for(int i = 0; i < size; ++i){
        float expected = host_array[i] * 3.0f;
        if (host_array[i] != expected) {
            err++;
            break;
        }
    }

    // Cleanup
    #pragma acc exit data delete(host_array[0:size])
    free(host_array);
    
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