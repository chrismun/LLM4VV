#include "acc_testsuite.h"
#ifndef T1
/*T1:acc on device,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int device_type = rand() % 3; // Randomly select a device type: acc_device_host, acc_device_not_host, or an accelerator device type
    int on_device = acc_on_device(device_type);

    if (device_type == acc_device_host && on_device == 0){
        err = 1;
    }
    else if (device_type == acc_device_not_host && on_device == 1){
        err = 1;
    }
    else if (device_type != acc_device_host && device_type != acc_device_not_host && on_device == 0){
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