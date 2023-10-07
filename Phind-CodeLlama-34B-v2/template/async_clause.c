#include "acc_testsuite.h"
#ifndef T1
//T1:async clause,V:2.7-3.3
int test1(){
    int err = 0;
    int async_value = 1;
    int async_value_noval = 0;
    int async_value_sync = 3;

    #pragma acc parallel async(async_value)
    {
        // Some parallel region code here
    }

    #pragma acc parallel async
    {
        // Some parallel region code here
    }

    #pragma acc parallel async(async_value_noval)
    {
        // Some parallel region code here
    }

    #pragma acc parallel async(async_value_sync)
    {
        // Some parallel region code here
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