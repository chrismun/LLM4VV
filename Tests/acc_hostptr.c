#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define NUM_TEST_CALLS 10
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    // Create a host pointer
    int *host_ptr = (int *)malloc(sizeof(int));
    if (host_ptr == NULL) {
        fprintf(stderr, "Failed to allocate host pointer\n");
        return 1;
    }

    // Set the value of the host pointer
    *host_ptr = 123;

    // Create an OpenACC device pointer
    int *dev_ptr = (int *)acc_hostptr(host_ptr);
    if (dev_ptr == NULL) {
        fprintf(stderr, "Failed to create OpenACC device pointer\n");
        return 1;
    }

    // Set the value of the OpenACC device pointer
    *dev_ptr = 456;

    // Check that the value of the host pointer has been updated
    if (*host_ptr != 456) {
        fprintf(stderr, "Host pointer was not updated correctly\n");
        err = 1;
    }

    // Free the host pointer
    free(host_ptr);

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