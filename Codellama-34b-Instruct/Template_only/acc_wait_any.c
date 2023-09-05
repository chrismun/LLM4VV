#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device array
    int *dev_array;
    acc_malloc(&dev_array, sizeof(int) * 10);

    // Initialize the device array with random values
    for (int i = 0; i < 10; i++) {
        dev_array[i] = rand() % 100;
    }

    // Create a host array
    int *host_array = (int *)acc_malloc(sizeof(int) * 10);

    // Copy the device array to the host array
    acc_memcpy(host_array, dev_array, sizeof(int) * 10);

    // Wait for the device array to be ready
    acc_wait(dev_array, 10);

    // Check if the device array is ready
    if (acc_is_ready(dev_array, 10) == 0) {
        // The device array is not ready, so we need to wait for it to be ready
        acc_wait(dev_array, 10);
    }

    // Copy the host array back to the device array
    acc_memcpy(dev_array, host_array, sizeof(int) * 10);

    // Free the device array
    acc_free(dev_array);

    // Free the host array
    acc_free(host_array);

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