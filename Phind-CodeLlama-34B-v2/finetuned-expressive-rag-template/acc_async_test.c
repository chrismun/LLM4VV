#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 10
#define SEED 1234

int test_acc_async_test() {
    int err = 0;
    srand(SEED);

    int async_queue = rand() % 100;
    int wait_arg = rand() % 100;
    int dev_num = rand() % acc_get_num_devices(acc_device_current);

    #pragma acc enter data copyin(async_queue, wait_arg, dev_num)

    #pragma acc parallel async(async_queue)
    {
        // Some parallel computation here
    }

    #pragma acc update self(async_queue)

    int result = acc_async_test(wait_arg);
    if (result == 0) {
        printf("acc_async_test failed\n");
        err = 1;
    }

    #pragma acc exit data delete(async_queue, wait_arg, dev_num)

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test_acc_async_test();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}