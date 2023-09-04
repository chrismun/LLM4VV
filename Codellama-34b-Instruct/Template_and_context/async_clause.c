#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc parallel async(acc_async_noval)
    {
        // Do some work
    }

    #pragma acc serial async(acc_async_sync)
    {
        // Do some work
    }

    #pragma acc kernels async(acc_async_noval)
    {
        // Do some work
    }

    #pragma acc data async(acc_async_sync)
    {
        // Do some work
    }

    #pragma acc enterdata async(acc_async_noval)
    {
        // Do some work
    }

    #pragma acc exitdata async(acc_async_sync)
    {
        // Do some work
    }

    #pragma acc update async(acc_async_noval)
    {
        // Do some work
    }

    #pragma acc wait async(acc_async_sync)
    {
        // Do some work
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