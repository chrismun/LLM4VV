#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
// T1:acc_get_device_num,V:2.7-3.3
int test1() {
    int err = 0;
    srand(42); // SEED

    // Initialize a device of default type to ensure acc_get_device_num can operate.
    acc_init(acc_device_default);
    int device_num = acc_get_device_num(acc_device_default);

    if(device_num == -1) {
        // This means no devices of the default type are present, or it is not supported, which is an error for this test.
        err = 1;
    } else {
        // Further verification can be done by setting the device and checking if the returned device number matches.
        acc_set_device_num(device_num, acc_device_default);
        int current_device = acc_get_device_num(acc_device_default);
        if(current_device != device_num) {
            err = 1; // Error if the set device and the queried device number don't match
        }
    }

    // Finalize to clean up
    acc_finalize(acc_device_default);
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
    #ifndef T1
    failed = 0;
    for (int x = 0; x < 1; ++x) { // Using 1 for simplicity, can be NUM_TEST_CALLS if defined elsewhere
        failed += test1();
    }
    if(failed != 0) {
        failcode += (1 << 0);
    }
    #endif
    return failcode;
}