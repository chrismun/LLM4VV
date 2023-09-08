#include "acc_testsuite.h"

#ifndef T1
//T1:acc get default async,V:2.7-3.3
int test1(){
    int err = 0;

    // Set the default async queue to a non-default value
    acc_set_default_async(acc_async_noval);

    // Get the default async queue
    int default_async = acc_get_default_async();

    // Check that the default async queue is the same as the one we set
    if (default_async != acc_async_noval) {
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