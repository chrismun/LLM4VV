#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Adjust these definitions as per your test suite's conventions
#define SEED 12345
#define NUM_TEST_CALLS 5
#define DEFAULT_ASYNC_QUEUE acc_async_sync

// Precision for floating-point comparisons
#define PRECISION 0.00001

#ifndef T1
// T1:runtime,V:1.0-2.7
int test_acc_get_default_async() {
    int err = 0;

    // Initially, the default asynchronous queue should match DEFAULT_ASYNC_QUEUE
    int default_async = acc_get_default_async();
    if (default_async != DEFAULT_ASYNC_QUEUE) {
        err++;
        printf("Initial acc_get_default_async() did not return DEFAULT_ASYNC_QUEUE as expected. Returned: %d\n", default_async);
    }

    // Change the default async queue using acc_set_default_async
    acc_set_default_async(1);
    default_async = acc_get_default_async();
    if (default_async != 1) {
        err++;
        printf("After acc_set_default_async(1), acc_get_default_async() did not return 1 as expected. Returned: %d\n", default_async);
    }

    // Reset default async queue back to DEFAULT_ASYNC_QUEUE for clean-up
    acc_set_default_async(DEFAULT_ASYNC_QUEUE);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_acc_get_default_async();
    }
    if (failed != 0) {
        failcode += (1 << 0);
        printf("Test FAILED. Errors: %d\n", failed);
    } else {
        printf("Test PASSED.\n");
    }
#endif

    return failcode;
}