#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Create a pointer to a shared memory region
    int *shared_ptr = (int *)acc_malloc(sizeof(int));

    // Create a pointer to a non-shared memory region
    int *non_shared_ptr = (int *)malloc(sizeof(int));

    // Initialize the shared memory region
    *shared_ptr = 1;

    // Initialize the non-shared memory region
    *non_shared_ptr = 2;

    // Copy the non-shared memory region to the shared memory region
    acc_copyin(non_shared_ptr, shared_ptr, sizeof(int));

    // Check that the shared memory region has been updated
    if (*shared_ptr != 2) {
        err = 1;
    }

    // Free the non-shared memory region
    free(non_shared_ptr);

    // Free the shared memory region
    acc_free(shared_ptr);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test multiple times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    // Print the results
    if (failcode != 0) {
        printf("FAIL: copyin clause failed\n");
    } else {
        printf("PASS: copyin clause passed\n");
    }

    return failcode;
}