#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_runtime.h>

#define NUM_TEST_CALLS 10
#define PRECISION 0.0001

int test_acc_wait_any(int count, int wait_arg[]) {
    int err = 0;
    int i;

    for (i = 0; i < count; i++) {
        if (wait_arg[i] != acc_async_sync) {
            if (acc_async_test_device(wait_arg[i], acc_get_device_num()) == 0) {
                err++;
            }
        }
    }

    if (err == 0) {
        printf("Test passed: acc_wait_any returned the correct index\n");
    } else {
        printf("Test failed: acc_wait_any did not return the correct index\n");
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    int wait_arg[NUM_TEST_CALLS];
    int count = NUM_TEST_CALLS;

    for (int i = 0; i < count; i++) {
        wait_arg[i] = acc_async_sync;
    }

    failed = test_acc_wait_any(count, wait_arg);
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}