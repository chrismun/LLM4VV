#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Allocate some memory on the device
    void *device_mem = acc_malloc(1024);
    if (device_mem == NULL) {
        fprintf(stderr, "Failed to allocate memory on device\n");
        return 1;
    }

    // Copy some data to the device
    void *host_mem = malloc(1024);
    if (host_mem == NULL) {
        fprintf(stderr, "Failed to allocate memory on host\n");
        return 1;
    }
    memset(host_mem, 0, 1024);
    acc_memcpy(device_mem, host_mem, 1024);

    // Copy the data back to the host using acc_copyout
    void *copyout_mem = malloc(1024);
    if (copyout_mem == NULL) {
        fprintf(stderr, "Failed to allocate memory for copyout\n");
        return 1;
    }
    acc_copyout(copyout_mem, 1024);

    // Check that the data was copied correctly
    if (memcmp(host_mem, copyout_mem, 1024) != 0) {
        fprintf(stderr, "Data was not copied correctly\n");
        return 1;
    }

    // Delete the data from the device using acc_delete
    acc_delete(device_mem, 1024);

    // Check that the data was deleted correctly
    if (acc_memcpy(device_mem, host_mem, 1024) == 0) {
        fprintf(stderr, "Data was not deleted correctly\n");
        return 1;
    }

    // Free the memory on the host and device
    free(host_mem);
    acc_free(device_mem);

    return 0;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}