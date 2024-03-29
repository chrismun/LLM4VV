#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:acc get default async,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int default_async = acc_get_default_async();
    if (default_async != acc_async_noval) {
        err = 1;
        printf("Default async value is not acc_async_noval\n");
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