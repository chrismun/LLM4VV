#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <acc_runtime.h>

#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    srand(SEED);

    // Allocate some memory on the device
    void *data_dev = acc_malloc(1024);
    if (data_dev == NULL) {
        err = 1;
    }

    // Map the device memory to a host address
    void *data_arg = acc_map_data(data_dev, 1024);
    if (data_arg == NULL) {
        err = 1;
    }

    // Use the host address to access the device memory
    memset(data_arg, 0, 1024);

    // Unmap the device memory
    acc_unmap_data(data_dev);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test multiple times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << 0);
        }
    }

    return failcode;
}