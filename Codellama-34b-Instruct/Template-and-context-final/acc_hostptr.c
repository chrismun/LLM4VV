#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    srand(SEED);

    // Create a device pointer
    void *data_dev = acc_deviceptr(malloc(100));

    // Get the host pointer associated with the device pointer
    void *host_ptr = acc_hostptr(data_dev);

    // Check if the host pointer is the same as the incoming address
    if (host_ptr != data_dev) {
        err = 1;
    }

    // Free the device pointer
    acc_free(data_dev);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 10 times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << 0);
        }
    }

    return failcode;
}