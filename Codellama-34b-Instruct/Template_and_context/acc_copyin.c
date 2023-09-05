#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    srand(SEED);

    // Allocate some memory on the host
    int *host_data = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        host_data[i] = i;
    }

    // Copy the data to the device using acc_copyin
    int *device_data = (int *)acc_copyin(host_data, sizeof(int) * 10);
    if (device_data == NULL) {
        printf("acc_copyin failed\n");
        err = 1;
    }

    // Verify that the data was copied correctly
    for (int i = 0; i < 10; i++) {
        if (device_data[i] != host_data[i]) {
            printf("Data mismatch at index %d: expected %d, got %d\n", i, host_data[i], device_data[i]);
            err = 1;
        }
    }

    // Free the device memory
    acc_free(device_data);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}