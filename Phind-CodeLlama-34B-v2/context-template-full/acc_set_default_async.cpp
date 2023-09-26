#include <iostream>
#include <cstdlib>
#include "acc_testsuite.h"
#ifndef T1
/*T1:acc set default async,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int async_arg = rand() % 2; // 0 for acc_async_noval, 1 for async_arg
    acc_set_default_async(async_arg);

    int async_default = acc_get_default_async();

    if (async_default != async_arg){
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