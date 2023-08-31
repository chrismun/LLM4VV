#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <accelerator.h>

#define NUM_TEST_CALLS 100
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    // Generate random data
    int *data = (int *)malloc(sizeof(int) * 100);
    for (int i = 0; i < 100; i++) {
        data[i] = rand();
    }

    // Copy data to device
    int *dev_data;
    acc_malloc((void **)&dev_data, sizeof(int) * 100);
    acc_memcpy(dev_data, data, sizeof(int) * 100);

    // Check if data is correctly copied
    for (int i = 0; i < 100; i++) {
        if (dev_data[i] != data[i]) {
            err = 1;
            break;
        }
    }

    // Free device memory
    acc_free(dev_data);

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