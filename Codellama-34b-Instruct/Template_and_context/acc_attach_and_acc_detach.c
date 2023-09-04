#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_runtime.h>

#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    srand(SEED);

    // Create a host pointer
    int *host_ptr = (int *)malloc(sizeof(int));
    *host_ptr = 1234;

    // Attach the host pointer to the device
    acc_attach(host_ptr);

    // Detach the host pointer from the device
    acc_detach(host_ptr);

    // Check that the host pointer is still valid
    if (*host_ptr != 1234) {
        err = 1;
    }

    // Free the host pointer
    free(host_ptr);

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

    // Print the result
    if (failcode == 0) {
        printf("All tests passed\n");
    } else {
        printf("Some tests failed\n");
    }

    return failcode;
}