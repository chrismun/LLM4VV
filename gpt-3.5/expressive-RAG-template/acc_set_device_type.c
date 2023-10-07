#include "acc_testsuite.h"
#ifndef T1
//T1: acc set device type, V: 2.7-3.3
int test1() {
    int err = 0;
    int result = 0;

    // Set device type to GPU
    #pragma acc set device_type(acc_device_nvidia)

    // Check the current device type
    #pragma acc parallel device_type(result)
    {
        if (result == acc_device_nvidia) {
            // Device type successfully set to GPU
            result = 1;
        } else {
            // Error: device type is not GPU
            err = 1;
        }
    }

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