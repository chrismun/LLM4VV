#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_runtime.h>

#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    srand(SEED);

    // Create a new async queue
    acc_async_queue_t queue = acc_async_queue_create(NULL, NULL, NULL);

    // Enqueue a wait operation on the async queue
    acc_wait_async(queue, 0);

    // Check if the wait operation has completed
    if (acc_async_queue_get_status(queue) == ACC_ASYNC_QUEUE_STATUS_COMPLETE) {
        printf("Wait operation completed successfully\n");
    } else {
        printf("Wait operation did not complete successfully\n");
        err = 1;
    }

    // Destroy the async queue
    acc_async_queue_destroy(queue);

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

    // Print the final result
    if (failcode == 0) {
        printf("All tests passed\n");
    } else {
        printf("Some tests failed\n");
    }

    return failcode;
}