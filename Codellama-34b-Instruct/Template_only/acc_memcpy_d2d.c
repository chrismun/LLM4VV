#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create two arrays on the host
    int *host_array1 = (int *)malloc(sizeof(int) * 10);
    int *host_array2 = (int *)malloc(sizeof(int) * 10);

    // Initialize the arrays with random values
    for (int i = 0; i < 10; i++) {
        host_array1[i] = rand();
        host_array2[i] = rand();
    }

    // Copy the arrays to the device
    int *device_array1 = (int *)acc_malloc(sizeof(int) * 10);
    int *device_array2 = (int *)acc_malloc(sizeof(int) * 10);
    acc_memcpy(device_array1, host_array1, sizeof(int) * 10);
    acc_memcpy(device_array2, host_array2, sizeof(int) * 10);

    // Perform a device-to-device copy
    acc_memcpy(device_array1, device_array2, sizeof(int) * 10);

    // Copy the arrays back to the host
    acc_memcpy(host_array1, device_array1, sizeof(int) * 10);
    acc_memcpy(host_array2, device_array2, sizeof(int) * 10);

    // Check that the arrays are equal
    for (int i = 0; i < 10; i++) {
        if (host_array1[i] != host_array2[i]) {
            err = 1;
            break;
        }
    }

    // Free the device memory
    acc_free(device_array1);
    acc_free(device_array2);

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