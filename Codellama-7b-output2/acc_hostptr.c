#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

#define NUM_TEST_CALLS 100
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    // Generate a random array of integers
    int *arr = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        arr[i] = rand() % 100;
    }

    // Create an OpenACC hostptr object
    acc_hostptr_t hostptr = acc_hostptr_create(arr, sizeof(int) * 10);

    // Verify that the hostptr object is valid
    if (hostptr == NULL) {
        printf("Error: hostptr is NULL\n");
        err = 1;
    }

    // Verify that the hostptr object has the correct size
    if (acc_hostptr_size(hostptr) != sizeof(int) * 10) {
        printf("Error: hostptr size is incorrect\n");
        err = 1;
    }

    // Verify that the hostptr object has the correct data
    int *hostptr_data = (int *)acc_hostptr_data(hostptr);
    for (int i = 0; i < 10; i++) {
        if (hostptr_data[i] != arr[i]) {
            printf("Error: hostptr data is incorrect\n");
            err = 1;
        }
    }

    // Free the hostptr object
    acc_hostptr_free(hostptr);

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