#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <acc_runtime.h>

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a host array
    int* host_array = (int*)malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        host_array[i] = i;
    }

    // Create a device array
    int* device_array = (int*)acc_malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        device_array[i] = i;
    }

    // Copy the host array to the device array
    acc_memcpy(device_array, host_array, 10 * sizeof(int));

    // Get the device pointer for the host array
    int* device_ptr = acc_deviceptr(host_array);

    // Check that the device pointer is not null
    if (device_ptr == NULL) {
        err = 1;
    }

    // Check that the device pointer points to the correct device memory
    if (device_ptr != device_array) {
        err = 1;
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