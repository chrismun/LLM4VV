#include "acc_testsuite.h"
#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    acc_device_t dev_type = acc_get_device_type();   // Get current device type.
    int dev_num = acc_get_device_num(dev_type);      // Get current device number.

    // Try initializing the default device. This should work if the device type is valid.
    // This serves as a basic test for acc_init functionality.
    acc_init(dev_type);
    if (!acc_on_device(dev_type)) {
        err = 1; // Error if acc_init does not set up the runtime properly
    }

    // Reset device number to test acc_init_device specifically
    acc_set_device_num(dev_num, dev_type); // Ensure we are using the same device as before
    acc_init_device(dev_num, dev_type);
    if (!acc_on_device(dev_type)) {
        err += 1; // Increment error if acc_init_device doesn't work as expected
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