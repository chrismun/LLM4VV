#include "acc_testsuite.h"

int acc_on_device(acc_device_t dev_type) {
    int result = 0;

    if (dev_type == acc_device_host) {
        result = 1;
    } else if (dev_type == acc_device_not_host) {
        result = 0;
    } else {
        result = 1;
    }

    return result;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + acc_on_device(acc_device_host);
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}