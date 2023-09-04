#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Create a shared memory region
    acc_init(acc_device_host);

    // Create a device memory region
    acc_init(acc_device_default);

    // Allocate memory for the data
    int *data = (int *)acc_malloc(sizeof(int) * 10);

    // Initialize the data
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }

    // Create a no_create clause
    acc_no_create(data);

    // Verify that the data is not present in the device memory
    if (acc_is_present(data, acc_device_default)) {
        printf("Data is present in device memory\n");
        err = 1;
    }

    // Verify that the data is not present in the shared memory
    if (acc_is_present(data, acc_device_host)) {
        printf("Data is present in shared memory\n");
        err = 1;
    }

    // Verify that the data is not present in the device memory
    if (acc_is_present(data, acc_device_default)) {
        printf("Data is present in device memory\n");
        err = 1;
    }

    // Verify that the data is not present in the shared memory
    if (acc_is_present(data, acc_device_host)) {
        printf("Data is present in shared memory\n");
        err = 1;
    }

    // Free the memory
    acc_free(data);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = failed + test1();
    }

    // Check if any tests failed
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}