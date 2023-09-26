#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
// T1: acc get default async, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    int expected = acc_get_default_async();

    #pragma acc setup enter data copyin(expected)

    #pragma acc parallel async(expected)
    {
        int async = acc_get_default_async();
        if (async != expected) {
            err = 1;
        }
    }

    #pragma acc wait

    #pragma acc exit data delete(expected)

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    return failcode;
}