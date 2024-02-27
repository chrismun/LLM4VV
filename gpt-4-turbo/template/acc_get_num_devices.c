#include "acc_testsuite.h"

#ifndef T1
//T1:{routine_host_data},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Try to get the number of devices for a specific type, here ACC_DEVICE_DEFAULT is used.
    // ACC_DEVICE_DEFAULT specifies the default device type. The actual device type can be any of the OpenACC devices.
    // Feel free to test with other device types e.g., ACC_DEVICE_NVIDIA, ACC_DEVICE_HOST etc.,
    int num_devices = acc_get_num_devices(ACC_DEVICE_DEFAULT);

    // Checking for error condition - the number of devices should not be negative
    if (num_devices < 0) {
        err = 1; // Set error if the implementation returns a negative number
    }

    // Optionally, further verification could be done by attempting to use the specified number of devices
    // in data movement or parallel constructs, to ensure the number reported is actually coherent with functional device usage.
    // However, such checks are beyond the basic verification aimed by this test.

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