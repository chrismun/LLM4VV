#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1(){
    int err = 0;
    srand(SEED);

    // Create an async queue
    int async_queue = acc_async_queue_create();

    // Create a device
    int device = acc_device_create();

    // Create a wait argument
    int wait_arg = acc_async_wait_create(async_queue, device);

    // Wait for the wait argument to complete
    acc_wait(wait_arg);

    // Check if the wait argument has completed
    if (acc_async_wait_complete(wait_arg) != 0) {
        err = 1;
    }

    // Clean up
    acc_async_queue_destroy(async_queue);
    acc_device_destroy(device);
    acc_async_wait_destroy(wait_arg);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    // Run the test
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}