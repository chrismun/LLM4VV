#include "acc_testsuite.h"
#include <stdio.h>

#ifndef T1
// T1:parallel,data,data-region,V:1.0-2.7
int test1() {
    int err = 0;
    int dev_num, dev_type;

    // Choose device number and device type
    dev_num = 0;
    dev_type = acc_device_nvidia;

    // Set the device number and device type
    acc_set_device_num(dev_num, dev_type);

    // Get the current device number
    int current_dev_num = acc_get_device_num(acc_device_nvidia);
    if (current_dev_num != dev_num) {
        err = 1;
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