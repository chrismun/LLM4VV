#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_runtime.h>

#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    srand(SEED);

    // Create a host array
    int* host_array = (int*)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        host_array[i] = i;
    }

    // Create a device array
    int* device_array = (int*)acc_malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        device_array[i] = i;
    }

    // Copy the host array to the device array
    acc_memcpy(device_array, host_array, sizeof(int) * 10);

    // Get the device pointer for the host array
    int* device_ptr = acc_deviceptr(host_array);

    // Check if the device pointer is valid
    if (device_ptr == NULL) {
        printf("Device pointer is NULL\n");
        err = 1;
    }

    // Check if the device pointer points to the correct location
    if (device_ptr != device_array) {
        printf("Device pointer does not point to the correct location\n");
        err = 1;
    }

    // Free the device array
    acc_free(device_array);

    // Free the host array
    free(host_array);

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