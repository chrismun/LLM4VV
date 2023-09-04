#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Create a device and activity queues
    int device = acc_create_device(acc_device_default);
    int queue = acc_create_queue(device);

    // Enqueue a wait operation on the queue
    acc_wait(queue, acc_async_sync);

    // Check if the wait operation has completed
    if (acc_get_queue_status(queue) == acc_queue_status_complete) {
        printf("Wait operation completed successfully\n");
    } else {
        printf("Wait operation did not complete\n");
        err = 1;
    }

    // Clean up
    acc_destroy_queue(queue);
    acc_destroy_device(device);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test multiple times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << 0);
        }
    }

    return failcode;
}