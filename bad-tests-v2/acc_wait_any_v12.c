#include "acc_testsuite.h"
#ifndef T1
//T1:acc wait any,V:2.7-3.3
int test1(){
    int err = 0;
    int async_queue[2];
    int async_queue_id;
    int dev_num = acc_get_device_num(acc_device_default);

    #pragma acc enter data copyin(async_queue[0:2])
    #pragma acc parallel async(async_queue[0])
    {
        // Do some work
    }
    #pragma acc parallel async(async_queue[1])
    {
        // Do some work
    }

    async_queue_id = acc_wait_any(2, async_queue);
    if (async_queue_id == -1) {
        err = 1;
    }

    async_queue_id = acc_wait_any_device(2, async_queue, dev_num);
    if (async_queue_id == -1) {
        err = 1;
    }

    #pragma acc exit data delete(async_queue[0:2])

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