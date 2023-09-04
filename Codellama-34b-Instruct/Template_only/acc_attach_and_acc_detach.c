#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device array
    int *device_array = (int *)acc_malloc(sizeof(int) * 10);

    // Attach the device array to the host
    acc_attach(device_array, 10);

    // Detach the device array from the host
    acc_detach(device_array);

    // Check that the device array is no longer attached to the host
    if (acc_is_attached(device_array)) {
        err = 1;
    }

    // Free the device array
    acc_free(device_array);

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