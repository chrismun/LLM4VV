#include "acc_testsuite.h"
#ifndef T1
//T1:acc async test,V:2.7-3.3
int test1(){
    int err = 0;
    int async_id = 1;
    int dev_num = 0;

    #pragma acc enter data copyin(async_id)
    #pragma acc parallel async(async_id)
    {
        // Do some work here
    }

    // Test acc_async_test
    if (acc_async_test(async_id) == 0) {
        err = 1;
    }

    // Test acc_async_test_device
    if (acc_async_test_device(async_id, dev_num) == 0) {
        err = 1;
    }

    // Test acc_async_test_all
    #pragma acc parallel async(async_id)
    {
        // Do some work here
    }
    if (acc_async_test_all() == 0) {
        err = 1;
    }

    // Test acc_async_test_all_device
    #pragma acc parallel async(async_id)
    {
        // Do some work here
    }
    if (acc_async_test_all_device(dev_num) == 0) {
        err = 1;
    }

    #pragma acc exit data delete(async_id)

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