#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:acc set default async,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int async_arg = rand() % 2;
    acc_set_default_async(async_arg);

    int async_default = acc_async_default;
    int async_noval = acc_async_noval;

    #pragma acc parallel async
    {
        // Empty parallel region to check if it goes to the correct async queue
    }

    if (async_arg == async_default){
        if (acc_async_test() != 0){
            err = 1;
        }
    } else if (async_arg == async_noval){
        if (acc_async_test() == 0){
            err = 1;
        }
    } else {
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