#include "acc_testsuite.h"
#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Ensure OpenACC is initialized.
    acc_init(acc_device_default);

    // Retrieve the current device type set in the OpenACC runtime.
    acc_device_t device_type_set = acc_get_device_type();
    
    // Assuming default device type is set; let's check against it.
    // One can make this dynamic by allowing environment variable to set expected device type for the test.
    acc_device_t expected_device_type = acc_device_default;  // This could be altered based on the actual expected device.

    if (device_type_set != expected_device_type) {
        err = 1;  // Error if the retrieved device type does not match expected.
    }

    // Finalize OpenACC
    acc_shutdown(acc_device_default);

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