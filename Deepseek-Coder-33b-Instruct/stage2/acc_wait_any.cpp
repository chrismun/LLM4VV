#include <openacc.h>
#include <iostream>

#ifndef T1
//T1:acc wait any,V:2.7-3.3
int test1(){
    int err = 0;
    int count = 10;
    int wait_arg[count];

    // Initialize the async arguments
    for (int i = 0; i < count; ++i) {
        wait_arg[i] = acc_async_sync;
    }

    // Wait for any async argument to complete
    int index = acc_wait_any(count, wait_arg);

    // Check if the returned index is valid
    if (index < 0 || index >= count) {
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