c
#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int count = 10;
    int wait_arg[count];
    int dev_num = 0;

    // Initialize wait_arg with random values
    for (int i = 0; i < count; i++) {
        wait_arg[i] = rand() % 100;
    }

    // Call acc_wait_any with count and wait_arg
    int ret = acc_wait_any(count, wait_arg);

    // Check if the return value is -1
    if (ret == -1) {
        // If the return value is -1, it means that all the elements in wait_arg are equal to acc_async_sync
        // or count is equal to 0, so we can't verify the implementation of acc_wait_any
        err = 1;
    } else {
        // If the return value is not -1, we can verify the implementation of acc_wait_any
        // Check if the return value is in the range of 0 to count-1
        if (ret < 0 || ret >= count) {
            // If the return value is not in the range of 0 to count-1, it means that the implementation of acc_wait_any is not correct
            err = 1;
        } else {
            // If the return value is in the range of 0 to count-1, we can verify the implementation of acc_wait_any_device
            // Call acc_wait_any_device with count, wait_arg, and dev_num
            ret = acc_wait_any_device(count, wait_arg, dev_num);

            // Check if the return value is -1
            if (ret == -1) {
                // If the return value is -1, it means that all the elements in wait_arg are equal to acc_async_sync
                // or count is equal to 0, so we can't verify the implementation of acc_wait_any_device
                err = 1;
            } else {
                // If the return value is not -1, we can verify the implementation of acc_wait_any_device
                // Check if the return value is in the range of 0 to count-1
                if (ret < 0 || ret >= count) {
                    // If the return value is not in the range of 0 to count-1, it means that the implementation of acc_wait_any_device is not correct
                    err = 1;
                }
            }
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}