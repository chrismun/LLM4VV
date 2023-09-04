#include "acc_testsuite.h"
#ifndef T2
//T2:serial,construct-independent,V:2.0-3.1
int test2() {
    int err = 0;
    int num_devices = acc_get_num_devices(acc_device_default);

    // If there is at least one device other than the default (host) device,
    if (num_devices > 1) {
        #pragma acc data copyin(num_devices)
        {
            int device_type = 0;
            #pragma acc parallel loop
            for (int x = 0; x < num_devices; ++x) {
                acc_device_type_t dev_type = acc_get_device_type(x);
                if (dev_type != acc_device_default) {
                    device_type = 1;
                }
            }

            // Check if device type is set on at least one device other than the default
            if (device_type == 0) {
                err += 1;
            }
        }
    }

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test2();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 1);
    }
#endif
    return failcode;
}