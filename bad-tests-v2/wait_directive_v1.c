#include "acc_testsuite.h"
#ifndef T1
//T1:wait directive,V:2.7-3.3
int test1(){
    int err = 0;
    int async = 1;
    int async_wait = 2;

    #pragma acc enter data copyin(async, async_wait)
    #pragma acc parallel async(async)
    {
        #pragma acc atomic update
        async_wait--;
    }
    #pragma acc wait(async)
    #pragma acc parallel async(async_wait)
    {
        #pragma acc atomic update
        async_wait--;
    }
    #pragma acc wait(async_wait)
    #pragma acc exit data delete(async, async_wait)

    if (async_wait != 0) {
        err = 1;
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