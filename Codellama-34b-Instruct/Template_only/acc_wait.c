#include "acc_testsuite.h"

//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device array
    int *dev_array;
    acc_malloc(&dev_array, sizeof(int) * 10);

    // Initialize the device array with random values
    for (int i = 0; i < 10; i++) {
        dev_array[i] = rand();
    }

    // Create a host array
    int *host_array = (int *)acc_malloc(sizeof(int) * 10);

    // Copy the device array to the host array
    acc_memcpy(host_array, dev_array, sizeof(int) * 10);

    // Wait for the copy to complete
    acc_wait(dev_array);

    // Check that the host array contains the same values as the device array
    for (int i = 0; i < 10; i++) {
        if (host_array[i] != dev_array[i]) {
            err = 1;
            break;
        }
    }

    // Free the device and host arrays
    acc_free(dev_array);
    acc_free(host_array);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    // Run the test
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}