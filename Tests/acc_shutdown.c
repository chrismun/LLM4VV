#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize the OpenACC runtime
    acc_init(acc_device_default);

    // Create a new OpenACC device
    acc_device_t device;
    acc_create_device(&device, acc_device_default);

    // Shut down the OpenACC runtime
    acc_shutdown(device);

    // Check if the OpenACC runtime is still active
    if (acc_is_active(device)) {
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