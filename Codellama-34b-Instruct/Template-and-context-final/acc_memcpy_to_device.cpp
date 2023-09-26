#include <iostream>
#include <cstdlib>
#include <cstring>

#include "acc_testsuite.h"

// T1:acc memcpy to device,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    // Allocate memory on the device
    int *data_dev_dest = (int *)acc_malloc(sizeof(int) * 10);
    int *data_host_src = (int *)malloc(sizeof(int) * 10);

    // Initialize data on the host
    for (int i = 0; i < 10; i++) {
        data_host_src[i] = i;
    }

    // Copy data from host to device
    acc_memcpy_to_device(data_dev_dest, data_host_src, sizeof(int) * 10);

    // Check that the data was copied correctly
    for (int i = 0; i < 10; i++) {
        if (data_dev_dest[i] != data_host_src[i]) {
            err = 1;
            break;
        }
    }

    // Free memory on the device
    acc_free(data_dev_dest);
    free(data_host_src);

    return err;
}

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

    return failcode;
}