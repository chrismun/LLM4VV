#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Create a device memory region
    acc_device_t device = acc_get_device(acc_device_default);
    acc_device_memory_t device_memory = acc_device_malloc(device, 1024);

    // Copy data to the device memory region
    int data[1024];
    for (int i = 0; i < 1024; i++) {
        data[i] = rand();
    }
    acc_memcpy_to_device(device_memory, data, 1024);

    // Verify that the data was copied correctly
    int *device_data = (int *)acc_device_memory_get_pointer(device_memory);
    for (int i = 0; i < 1024; i++) {
        if (device_data[i] != data[i]) {
            err = 1;
            break;
        }
    }

    // Free the device memory region
    acc_device_free(device_memory);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test multiple times to ensure it passes consistently
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}