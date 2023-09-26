#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Set the device number to a random value
    int dev_num = rand() % 10;

    // Set the device type to a random value
    acc_device_t dev_type = (acc_device_t)rand() % 2;

    // Call acc_set_device_num with the random device number and type
    acc_set_device_num(dev_num, dev_type);

    // Check that the device number was set correctly
    if (acc_get_device_num() != dev_num) {
        err = 1;
    }

    // Check that the device type was set correctly
    if (acc_get_device_type() != dev_type) {
        err = 1;
    }

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