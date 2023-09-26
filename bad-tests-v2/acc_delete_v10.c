#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a new device
    acc_device_t device = acc_get_device(acc_device_default);

    // Allocate memory on the device
    void *device_ptr = acc_malloc(device, 1024);

    // Delete the memory on the device
    acc_delete(device_ptr);

    // Check that the memory has been deleted
    if (acc_is_present(device_ptr) != 0) {
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