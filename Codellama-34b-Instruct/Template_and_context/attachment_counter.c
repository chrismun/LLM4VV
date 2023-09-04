#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    srand(SEED);

    // Allocate a pointer in device memory
    int *ptr = (int *)acc_malloc(sizeof(int));

    // Set the attachment counter to 0
    acc_attach_counter(ptr, 0);

    // Attach the pointer to a device address
    acc_attach(ptr, sizeof(int), 0);

    // Increment the attachment counter
    acc_attach_counter(ptr, 1);

    // Detach the pointer from the device address
    acc_detach(ptr);

    // Decrement the attachment counter
    acc_attach_counter(ptr, -1);

    // Check if the attachment counter is 0
    if (acc_attach_counter(ptr) != 0) {
        err = 1;
    }

    // Free the pointer in device memory
    acc_free(ptr);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test NUM_TEST_CALLS times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}