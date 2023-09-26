#include "acc_testsuite.h"

#ifndef T1
//T1:wait clause,V:2.7-3.3
int test1(){
    int err = 0;

    // Set up the device and activity queues
    acc_set_device_num(1, 1);
    acc_set_async(1, 1);

    // Enqueue some operations on the device
    acc_parallel(1, 1, 1, 1);
    acc_parallel(1, 1, 1, 1);

    // Wait for the operations to complete
    acc_wait(1, 1);

    // Check that the operations have completed
    if (acc_get_device_num(1) != 1 || acc_get_async(1) != 1) {
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