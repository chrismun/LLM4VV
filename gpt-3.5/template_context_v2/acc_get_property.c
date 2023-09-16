#include "acc_testsuite.h"
#ifndef T1
// T1: acc get property,V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);

    // Declare device variable
    int *dev_arr = (int*)malloc(N * sizeof(int));

    // Allocate memory on device
    #pragma acc enter data create(dev_arr[:N])

    // Get device type property
    acc_device_t dev_type_prop = acc_get_property(acc_get_device_num(acc_get_device_type()), acc_property_device_type);
    
    // Check if the device type is acc_device_none
    if (dev_type_prop != acc_device_none) {
        err = 1;
    }

    // Free memory on device
    #pragma acc exit data delete(dev_arr[:N])
    free(dev_arr);

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