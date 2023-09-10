#include "acc_testsuite.h"

#ifndef T1
//T1:acc attach,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device array
    int *device_array = (int *)acc_malloc(sizeof(int) * 10);

    // Attach the device array to the host
    acc_attach(device_array, sizeof(int) * 10);

    // Perform some operations on the device array
    for (int i = 0; i < 10; i++) {
        device_array[i] = i;
    }

    // Detach the device array from the host
    acc_detach(device_array);

    // Check that the device array has been updated
    for (int i = 0; i < 10; i++) {
        if (device_array[i] != i) {
            err = 1;
            break;
        }
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