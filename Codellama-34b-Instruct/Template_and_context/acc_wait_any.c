#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_runtime.h>

#define NUM_TEST_CALLS 10

int test1() {
    int err = 0;
    srand(SEED);

    int count = 10;
    int wait_arg[count];
    int dev_num = 0;

    for (int i = 0; i < count; i++) {
        wait_arg[i] = acc_async_sync;
    }

    int result = acc_wait_any(count, wait_arg);

    if (result != -1) {
        printf("acc_wait_any returned %d, expected -1\n", result);
        err = 1;
    }

    result = acc_wait_any_device(count, wait_arg, dev_num);

    if (result != -1) {
        printf("acc_wait_any_device returned %d, expected -1\n", result);
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = failed + test1();
    }

    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}