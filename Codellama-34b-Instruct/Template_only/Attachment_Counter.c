#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define NUM_TEST_CALLS 100

int test1() {
    int err = 0;
    srand(SEED);

    // Create an attachment counter
    acc_attach_counter(1, 1, 1, 1, 1, 1, 1, 1);

    // Verify that the attachment counter is working properly
    if (acc_get_counter(1) != 1) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test multiple times to ensure that the attachment counter is working properly
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}