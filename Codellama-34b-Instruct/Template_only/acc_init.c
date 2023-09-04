#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize the OpenACC runtime
    acc_init();

    // Create a new OpenACC device
    acc_device_t device = acc_create_device(ACC_DEVICE_TYPE_GPU);

    // Set the device as the current device
    acc_set_device(device);

    // Allocate memory on the device
    acc_malloc(1024);

    // Initialize the memory on the device
    acc_init_memory(device, 1024);

    // Free the memory on the device
    acc_free(device);

    // Destroy the device
    acc_destroy_device(device);

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