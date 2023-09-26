#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_DEVICES 2
#define NUM_TEST_CALLS 10

int main() {
    int failcode = 0;
    int failed;

    // Initialize the OpenACC runtime
    acc_init(acc_device_default);

    // Set the number of devices to 2
    acc_set_device_num(NUM_DEVICES);

    // Allocate memory for the device arrays
    real_t *a = (real_t *)acc_malloc(sizeof(real_t) * NUM_DEVICES);
    real_t *b = (real_t *)acc_malloc(sizeof(real_t) * NUM_DEVICES);

    // Initialize the device arrays
    for (int i = 0; i < NUM_DEVICES; i++) {
        a[i] = i;
        b[i] = 0;
    }

    // Set the device number to 0
    acc_set_device_num(0);

    // Copy the data from the host to the device
    acc_memcpy_to_device(a, b, sizeof(real_t) * NUM_DEVICES);

    // Set the device number to 1
    acc_set_device_num(1);

    // Copy the data from the host to the device
    acc_memcpy_to_device(a, b, sizeof(real_t) * NUM_DEVICES);

    // Set the device number to 0
    acc_set_device_num(0);

    // Copy the data from the device to the host
    acc_memcpy_from_device(a, b, sizeof(real_t) * NUM_DEVICES);

    // Check the results
    for (int i = 0; i < NUM_DEVICES; i++) {
        if (a[i] != b[i]) {
            printf("Error: a[%d] = %f, b[%d] = %f\n", i, a[i], i, b[i]);
            failcode = 1;
        }
    }

    // Clean up
    acc_free(a);
    acc_free(b);

    return failcode;
}