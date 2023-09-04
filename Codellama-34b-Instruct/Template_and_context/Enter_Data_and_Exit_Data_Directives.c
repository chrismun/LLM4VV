#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openacc.h>

#define SEED 12345
#define NUM_TEST_CALLS 100

int test1() {
    int err = 0;
    srand(SEED);

    // Create a new device memory region
    acc_device_t device = acc_get_device_default();
    acc_device_memory_t memory = acc_malloc(device, 1024);

    // Enter data into the device memory region
    acc_enter_data(memory, 0, 1024, 0);

    // Copy data from local memory to device memory
    acc_copyin(memory, 0, 1024, 0);

    // Wait for the copy to complete
    acc_wait(memory, 0, 1024, 0);

    // Exit data from the device memory region
    acc_exit_data(memory, 0, 1024, 0);

    // Free the device memory region
    acc_free(memory);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 100 times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    // Print the result
    if (failcode != 0) {
        printf("Test failed with failcode %d\n", failcode);
    } else {
        printf("Test passed\n");
    }

    return failcode;
}