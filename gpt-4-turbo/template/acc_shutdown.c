#include "acc_testsuite.h"
#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    const int size = 1000;
    float *host_array = (float*)malloc(size * sizeof(float));
    float *device_array;
    int i;

    // Initialize host array with random values
    for (i = 0; i < size; ++i){
        host_array[i] = (float)rand() / (float)(RAND_MAX / 100);
    }

    // Allocate and copy to device
    #pragma acc enter data copyin(host_array[0:size])
    device_array = acc_deviceptr(host_array);

    // Perform some operations on the device
    #pragma acc parallel loop present(device_array[0:size])
    for (i = 0; i < size; ++i){
        device_array[i] = device_array[i] + 1.0f;
    }

    // Shutdown OpenACC runtime
    acc_shutdown(acc_device_default);

    // Attempt to perform an operation after shutdown
    #pragma acc enter data create(host_array[0:size])
    device_array = acc_deviceptr(host_array);

    if (device_array != NULL) {
        err = 1; // If we are able to obtain a device pointer, shutdown failed to properly disable OpenACC operations.
    }

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