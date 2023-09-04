#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Create a pointer to a variable in shared memory
    int *ptr = (int *)malloc(sizeof(int));

    // Set the value of the variable in shared memory
    *ptr = 12345;

    // Attach the pointer to the device memory
    acc_attach(ptr, sizeof(int));

    // Increment the attachment counter for the pointer
    acc_attach_inc(ptr);

    // Detach the pointer from the device memory
    acc_detach(ptr);

    // Decrement the attachment counter for the pointer
    acc_detach_dec(ptr);

    // Check if the attachment counter is zero
    if (acc_attach_get(ptr) == 0) {
        // The attachment counter is zero, so the pointer is not attached to the device memory
        err = 1;
    }

    // Free the memory allocated for the pointer
    free(ptr);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test function NUM_TEST_CALLS times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    // Return the failcode
    return failcode;
}