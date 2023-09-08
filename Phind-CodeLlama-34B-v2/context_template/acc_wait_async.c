#include "acc_testsuite.h"
#ifndef T1
//T1:acc wait async,V:2.7-3.3
int test1(){
    int err = 0;
    int async_arg = 1;
    int wait_arg = 2;
    int dev_num = 0;

    #pragma acc enter data copyin(async_arg, wait_arg, dev_num)
    #pragma acc parallel async(async_arg)
    {
        #pragma acc update device(async_arg, wait_arg, dev_num)
        #pragma acc wait(wait_arg) async(async_arg)
    }
    #pragma acc parallel async(async_arg)
    {
        #pragma acc update device(async_arg, wait_arg, dev_num)
        #pragma acc wait(dev_num: dev_num, queues: wait_arg) async(async_arg)
    }
    #pragma acc parallel async(async_arg)
    {
        #pragma acc update device(async_arg, wait_arg, dev_num)
        #pragma acc wait async(async_arg)
    }
    #pragma acc parallel async(async_arg)
    {
        #pragma acc update device(async_arg, wait_arg, dev_num)
        #pragma acc wait(dev_num: dev_num) async(async_arg)
    }
    #pragma acc exit data delete(async_arg, wait_arg, dev_num)

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