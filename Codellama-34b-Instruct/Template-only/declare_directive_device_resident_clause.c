#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Declare a device-resident variable
    int *device_resident_var;

    // Allocate memory on the device for the variable
    device_resident_var = (int *)acc_malloc(sizeof(int));

    // Initialize the variable on the device
    *device_resident_var = 1;

    // Use the variable in a kernel
    #pragma acc parallel loop device_resident(device_resident_var)
    for (int i = 0; i < 10; i++) {
        device_resident_var[i] = i;
    }

    // Check that the variable was updated correctly
    for (int i = 0; i < 10; i++) {
        if (device_resident_var[i] != i) {
            err = 1;
            break;
        }
    }

    // Free the memory on the device
    acc_free(device_resident_var);

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