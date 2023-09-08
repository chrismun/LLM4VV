#include "acc_testsuite.h"
#ifndef T1
//T1:wait directive,V:2.7-3.3
int test1(){
    int err = 0;
    int async = 1;
    int async_queue = 1;

    #pragma acc enter data copyin(async)
    #pragma acc enter data copyin(async_queue)

    #pragma acc parallel async(async)
    {
        #pragma acc update device(async)
    }

    #pragma acc parallel async(async_queue)
    {
        #pragma acc update device(async_queue)
    }

    #pragma acc wait(async)
    #pragma acc wait(async_queue)

    #pragma acc exit data delete(async)
    #pragma acc exit data delete(async_queue)

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