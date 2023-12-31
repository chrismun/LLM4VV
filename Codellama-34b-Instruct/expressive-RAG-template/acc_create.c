#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a new array on the device
    int *device_array = (int *)acc_malloc(sizeof(int) * 10);

    // Initialize the array with random values
    for (int i = 0; i < 10; i++) {
        device_array[i] = rand();
    }

    // Create a new array on the host
    int *host_array = (int *)malloc(sizeof(int) * 10);

    // Copy the device array to the host array
    acc_memcpy(host_array, device_array, sizeof(int) * 10);

    // Verify that the host array contains the same values as the device array
    for (int i = 0; i < 10; i++) {
        if (host_array[i] != device_array[i]) {
            err = 1;
            break;
        }
    }

    // Free the device array
    acc_free(device_array);

    // Free the host array
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