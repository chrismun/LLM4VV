#include "acc_testsuite.h"

int acc_async_test(int wait_arg) {
    int err = 0;
    srand(SEED);

    if (wait_arg < 0 || wait_arg >= ACC_ASYNC_QUEUE_COUNT) {
        err = 1;
    }

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + acc_async_test(x);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}