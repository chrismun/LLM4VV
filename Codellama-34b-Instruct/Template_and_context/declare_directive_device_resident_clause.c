#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    srand(SEED);

    // Allocate memory for the device resident variable
    int *device_resident_var = (int *)acc_malloc(sizeof(int));

    // Initialize the device resident variable
    *device_resident_var = 1;

    // Verify that the device resident variable is accessible from the host
    if (*device_resident_var != 1) {
        err = 1;
    }

    // Free the device resident variable
    acc_free(device_resident_var);

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

    // Print the result
    if (failcode != 0) {
        printf("Device resident variable test failed\n");
    } else {
        printf("Device resident variable test passed\n");
    }

    return failcode;
}