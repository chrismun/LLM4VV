#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Create a device array
    int *dev_array = (int *)acc_malloc(sizeof(int) * 10);

    // Initialize the device array with random values
    for (int i = 0; i < 10; i++) {
        dev_array[i] = rand();
    }

    // Create a host array
    int *host_array = (int *)malloc(sizeof(int) * 10);

    // Copy the device array to the host array
    acc_memcpy(host_array, dev_array, sizeof(int) * 10);

    // Check that the host array contains the same values as the device array
    for (int i = 0; i < 10; i++) {
        if (host_array[i] != dev_array[i]) {
            err = 1;
            break;
        }
    }

    // Free the device array
    acc_free(dev_array);

    // Free the host array
    free(host_array);

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
        printf("The auto clause is not working properly\n");
    } else {
        printf("The auto clause is working properly\n");
    }

    return failcode;
}