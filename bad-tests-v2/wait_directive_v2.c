#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Create a device and activity queue
    int devnum = rand() % 10;
    int queue = rand() % 10;
    int async = rand() % 10;

    // Enqueue an asynchronous operation on the activity queue
    int result = acc_async(devnum, queue, async);

    // Wait for the operation to complete
    acc_wait(devnum, queue);

    // Check the result
    if (result != 0) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    // Run the test 10 times
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}