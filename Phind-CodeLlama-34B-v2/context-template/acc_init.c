#include "acc_testsuite.h"
#ifndef T1
//T1:acc init,V:2.7-3.3
int test1(){
    int err = 0;

    // Call acc_init with a valid device type
    acc_init(acc_device_default);

    // Call acc_init_device with a valid device type and device number
    int device_num = 0;
    acc_init_device(device_num, acc_device_default);

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