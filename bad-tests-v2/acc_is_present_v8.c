#include "acc_testsuite.h"

int acc_is_present(void *data_arg, size_t bytes) {
    int err = 0;
    if (data_arg == NULL) {
        err = 1;
    } else {
        // Check if the data is in shared memory
        if (acc_is_shared(data_arg, bytes)) {
            err = 1;
        }
        // Check if the data is present in the current device memory
        if (acc_is_present_in_device(data_arg, bytes)) {
            err = 1;
        }
    }
    return err;
}

int main() {
    int failcode = 0;
    int failed;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = acc_is_present(NULL, 0);
        if (failed != 0) {
            failcode = failcode + (1 << 0);
        }
    }
    return failcode;
}