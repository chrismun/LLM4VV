#include "acc_testsuite.h"
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstring>

#ifndef T1
/*T1:acc get default async,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int async_default = acc_get_default_async();
    if (async_default != acc_async_noval){
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