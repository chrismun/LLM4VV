#include "acc_testsuite.h"

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1() {
    int err = 0;

    acc_init(acc_device_default); // Initialize OpenACC runtime

    acc_device_t device_type = acc_get_device_type(); // Get the current device type
    if (device_type != acc_device_default) {
        err = 1;
    }

    acc_set_device_type(acc_device_nvidia); // Set the device type to NVIDIA GPU
    device_type = acc_get_device_type(); // Get the updated device type
    if (device_type != acc_device_nvidia) {
        err = 1;
    }

    acc_set_device_type(acc_device_host); // Set the device type to host
    device_type = acc_get_device_type();
    if (device_type != acc_device_host) {
        err = 1;
    }

    acc_shutdown(acc_device_default); // Shutdown OpenACC runtime

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}