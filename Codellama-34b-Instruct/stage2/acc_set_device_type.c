#include "acc_testsuite.h"

#ifndef T1
//T1:acc set device type,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Set the device type to a random value
    int dev_type = rand() % 2;
    acc_set_device_type(dev_type);

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