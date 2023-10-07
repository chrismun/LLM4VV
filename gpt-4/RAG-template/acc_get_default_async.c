#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
//T1:acc get default async,V:2.7-3.3
int test1(){
    int async_val;
    int err = 0;
    
    #pragma acc parallel copy(async_val)
    {
        async_val = acc_get_default_async();
    }

    // The OpenACC Specification states: 
    // "If the routine is called outside any async clause, 
    // it will return acc_async_sync."
    if(async_val != acc_async_sync){
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
    int x;
    for (x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}