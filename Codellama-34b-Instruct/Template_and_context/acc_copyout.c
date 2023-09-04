#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 100

int test1() {
    int err = 0;
    srand(SEED);

    // Allocate memory for the data section
    void *data_arg = malloc(sizeof(int) * 10);
    if (data_arg == NULL) {
        fprintf(stderr, "Failed to allocate memory for data section\n");
        return 1;
    }

    // Initialize the data section
    for (int i = 0; i < 10; i++) {
        ((int *)data_arg)[i] = i;
    }

    // Copy the data section to the device
    acc_copyout(data_arg, sizeof(int) * 10);

    // Delete the data section from the device
    acc_delete(data_arg, sizeof(int) * 10);

    // Check that the data section has been deallocated
    if (acc_is_present(data_arg, sizeof(int) * 10)) {
        fprintf(stderr, "Data section is still present in device memory\n");
        err = 1;
    }

    // Free the memory for the data section
    free(data_arg);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 100 times
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed) {
            failcode = failcode + (1 << x);
        }
    }

    // Print the result
    if (failcode) {
        printf("Test failed with failcode %d\n", failcode);
    } else {
        printf("Test passed\n");
    }

    return failcode;
}