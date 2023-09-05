#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_runtime.h>

#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    srand(SEED);

    // Allocate memory on the device
    void *data_dev = acc_malloc(1024);
    if (data_dev == NULL) {
        err = 1;
    }

    // Copy data from the device to the host
    void *data_host = acc_malloc(1024);
    if (data_host == NULL) {
        err = 1;
    }

    // Copy data from the device to the host
    acc_memcpy_from_device(data_host, data_dev, 1024);

    // Check that the data was copied correctly
    if (memcmp(data_host, data_dev, 1024) != 0) {
        err = 1;
    }

    // Free memory on the device
    acc_free(data_dev);
    acc_free(data_host);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test multiple times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}