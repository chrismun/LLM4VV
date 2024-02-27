#include "acc_testsuite.h"
#ifndef T1
// T1:{data deviceptr},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // The size for the test
    int size = 1024;
    int *host_array = (int*)malloc(size * sizeof(int));
    int *device_array;
    int *deviceptr_array;

    // Initializing host array with random data
    for (int i = 0; i < size; i++) {
        host_array[i] = rand() / (RAND_MAX / 100);
    }

    // Explicitly allocating memory on the device and copying host array to device
    #pragma acc enter data create(device_array[0:size])
    #pragma acc parallel loop copyin(host_array[0:size])
    for(int i = 0; i < size; i++){
        device_array[i] = host_array[i];
    }

    // Attaching the device pointer to be used in a data region using the deviceptr clause
    deviceptr_array = device_array;

    // Verifying that the deviceptr points to the correct data by performing a dummy operation
    #pragma acc parallel loop deviceptr(deviceptr_array)
    for (int i = 0; i < size; i++) {
        deviceptr_array[i] += 1;
    }

    // Copying data back to host for verification
    #pragma acc exit data copyout(host_array[0:size]) delete(device_array[0:size])

    // Verifying data correctness
    for (int i = 0; i < size; i++) {
        if (host_array[i] != (rand() / (RAND_MAX / 100)) + 1) {
            err++;
            break;
        }
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