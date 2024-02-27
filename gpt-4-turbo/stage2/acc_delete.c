#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef SEED
#define SEED 921
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// T1:acc delete, V:2.7-3.3
int test_acc_delete() {
    int err = 0;
    srand(SEED);
    size_t bytes = sizeof(int);
    int *data_host = (int *)malloc(bytes);
    *data_host = rand(); // Fill with random data

    // Allocate and initialize data on the device
    #pragma acc enter data copyin(data_host[0:1])

    // Delete data from device memory
    #pragma acc exit data delete(data_host[0:1])

    // At this point data_host should not be present on the device
    // Trying to perform operation on it without copying back should result in error
    int devicePresent = acc_is_present(data_host, bytes);

    if (devicePresent) {
        printf("Error: data_host should not be present on the device after acc_delete.\n");
        err += 1;
    } else {
        printf("Test passed: data_host is correctly not present on the device after acc_delete.\n");
    }

    free(data_host); // Cleanup host memory

    return err;
}

int main() {
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_acc_delete();
    }
    if (failed != 0) {
        failcode += (1 << 0);
    }
    return failcode;
}