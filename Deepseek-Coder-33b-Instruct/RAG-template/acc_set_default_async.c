#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;

    // Set the default asynchronous behavior mode to acc_async_sync
    acc_set_default_async(acc_async_sync);

    // Check if the default asynchronous behavior mode is set to acc_async_sync
    if (acc_get_default_async() != acc_async_sync) {
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