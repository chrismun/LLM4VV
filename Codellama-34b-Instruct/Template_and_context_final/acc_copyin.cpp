c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Allocate host memory for data
    int *data = (int *)malloc(sizeof(int) * 10);
    if (data == NULL) {
        printf("Failed to allocate host memory\n");
        return 1;
    }

    // Initialize data on host
    for (int i = 0; i < 10; i++) {
        data[i] = rand();
    }

    // Copy data from host to device using acc_copyin
    int *device_data = (int *)acc_copyin(data, sizeof(int) * 10);
    if (device_data == NULL) {
        printf("Failed to copy data to device\n");
        return 1;
    }

    // Read data back from device and compare with original data on host
    for (int i = 0; i < 10; i++) {
        if (device_data[i] != data[i]) {
            printf("Data mismatch at index %d: expected %d, got %d\n", i, data[i], device_data[i]);
            err = 1;
        }
    }

    // Free device memory
    acc_free(device_data);

    // Free host memory
    free(data);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run test1 10 times
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    // Return failcode
    return failcode;
}