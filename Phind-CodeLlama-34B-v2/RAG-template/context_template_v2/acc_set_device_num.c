#include "acc_testsuite.h"
#ifndef T1
//T1:acc set device num,V:2.7-3.3
int test1(){
    int err = 0;
    int dev_num = 0;
    acc_device_t dev_type = acc_device_default;

    // Set device number
    acc_set_device_num(dev_num, dev_type);

    // Check if the device number was set correctly
    if (acc_get_device_num(dev_type) != dev_num) {
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