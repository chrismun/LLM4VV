#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device array
    int *dev_array = (int *)acc_malloc(sizeof(int) * 10);

    // Set the device array to a random value
    for (int i = 0; i < 10; i++) {
        dev_array[i] = rand();
    }

    // Get the device array's properties
    acc_get_property(dev_array, ACC_PROPERTY_DEVICE_TYPE, &err);
    acc_get_property(dev_array, ACC_PROPERTY_DEVICE_ID, &err);
    acc_get_property(dev_array, ACC_PROPERTY_DEVICE_NAME, &err);

    // Check that the properties are correct
    if (err != 0) {
        return 1;
    }

    // Free the device array
    acc_free(dev_array);

    return 0;
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