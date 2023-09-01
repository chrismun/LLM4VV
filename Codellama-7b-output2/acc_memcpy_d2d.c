#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 100
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    // Generate random data
    int *data1 = (int *)malloc(sizeof(int) * 100);
    int *data2 = (int *)malloc(sizeof(int) * 100);
    for (int i = 0; i < 100; i++) {
        data1[i] = rand();
        data2[i] = rand();
    }

    // Copy data to device
    int *dev_data1;
    int *dev_data2;
    acc_malloc((void **)&dev_data1, sizeof(int) * 100);
    acc_malloc((void **)&dev_data2, sizeof(int) * 100);
    acc_memcpy(dev_data1, data1, sizeof(int) * 100);
    acc_memcpy(dev_data2, data2, sizeof(int) * 100);

    // Perform memcpy on device
    acc_memcpy(dev_data1, dev_data2, sizeof(int) * 100);

    // Copy data back to host
    acc_memcpy(data1, dev_data1, sizeof(int) * 100);
    acc_memcpy(data2, dev_data2, sizeof(int) * 100);

    // Check if data is correct
    for (int i = 0; i < 100; i++) {
        if (data1[i] != data2[i]) {
            err = 1;
            break;
        }
    }

    // Free memory
    acc_free(dev_data1);
    acc_free(dev_data2);
    free(data1);
    free(data2);

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