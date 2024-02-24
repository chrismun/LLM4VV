#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:acc wait async,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int async = acc_async_sync;
    int wait_async = acc_async_sync;

    #pragma acc enter data copyin(wait_async)
    #pragma acc parallel async(async)
    {
        #pragma acc loop
        for (int x = 0; x < 100; ++x){
            // do some work
        }
    }

    #pragma acc update self(wait_async)
    if (wait_async != async){
        err = 1;
    }

    acc_wait_async(wait_async, async);

    #pragma acc update self(wait_async)
    if (wait_async != async){
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