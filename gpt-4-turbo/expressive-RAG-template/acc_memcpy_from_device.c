#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include <string.h> // For memcmp()

// Define constants for the test
#define SEED 12345
#define NUM_TEST_CALLS 10
#define DATA_SIZE 1024 // size of data array

#ifndef T1
// T1:acc memcpy from device, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    
    // Host and device data pointers
    int *host_data = (int *)malloc(DATA_SIZE * sizeof(int));
    int *device_data;

    // Allocating memory on the device
    device_data = (int *)acc_malloc(DATA_SIZE * sizeof(int));
    
    // Verify malloc succeeded
    if (device_data == NULL) {
        printf("Device memory allocation failed.\n");
        free(host_data);
        return 1; // error
    }
    
    // Initialize device memory with test data
#pragma acc parallel loop copyin(device_data[0:DATA_SIZE])
    for(int i = 0; i < DATA_SIZE; i++) {
        device_data[i] = i;
    }
    
    // Use acc_memcpy_from_device to copy data back to host
    acc_memcpy_from_device(host_data, device_data, DATA_SIZE * sizeof(int));

    // Verify the data copied matches original test data
    for(int i = 0; i < DATA_SIZE; i++) {
        if (host_data[i] != i) {
            err = 1; // If data does not match, set err to nonzero
            break;
        }
    }

    // Cleanup
    free(host_data);
    acc_free(device_data);
    
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    if(failcode == 0) {
        printf("Test passed.\n");
    } else {
        printf("Test failed.\n");
    }
    return failcode;
}