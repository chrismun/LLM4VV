#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device resident array
    int *dev_array = (int *)acc_malloc(sizeof(int) * 10);

    // Set the device resident flag
    acc_set_device_resident(dev_array, 10);

    // Verify that the device resident flag is set
    if (acc_get_device_resident(dev_array) != 10) {
        err = 1;
    }

    // Free the device resident array
    acc_free(dev_array);

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