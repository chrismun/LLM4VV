#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:acc wait any,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int count = 10;
    int wait_arg[count];

    // Initialize wait_arg with acc_async_sync
    for (int i = 0; i < count; ++i) {
        wait_arg[i] = acc_async_sync;
    }

    // Call acc_wait_any
    int result = acc_wait_any(count, wait_arg);

    // Check if the result is -1
    if (result != -1) {
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