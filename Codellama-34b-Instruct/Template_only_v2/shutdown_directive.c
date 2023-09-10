#include "acc_testsuite.h"

#ifndef T1
//T1:shutdown directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device
    acc_device_t device = acc_get_device(acc_device_default);

    // Create a queue
    acc_queue_t queue = acc_queue_create(device, acc_async);

    // Shut down the device
    acc_device_shutdown(device);

    // Check that the device is shut down
    if (acc_device_is_shutdown(device)) {
        err = 1;
    }

    // Clean up
    acc_queue_destroy(queue);

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