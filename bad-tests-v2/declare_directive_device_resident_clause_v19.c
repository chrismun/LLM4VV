#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    srand(SEED);

    // Allocate memory for the variable in device memory
    int *x = (int *)acc_malloc(sizeof(int));

    // Set the value of the variable in device memory
    *x = 1;

    // Verify that the value of the variable in device memory is correct
    if (*x != 1) {
        err = 1;
    }

    // Free the memory for the variable in device memory
    acc_free(x);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test NUM_TEST_CALLS times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << 0);
        }
    }

    return failcode;
}