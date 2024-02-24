#include "acc_testsuite.h"
#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    acc_device_t dev_type = acc_get_device_type();

    if (dev_type == acc_device_default) {
        printf("Default device type\n");
    } else if (dev_type == acc_device_nvidia) {
        printf("NVIDIA GPU device type\n");
    } else if (dev_type == acc_device_radeon) {
        printf("AMD GPU device type\n");
    } else if (dev_type == acc_device_xeonphi) {
        printf("Xeon Phi device type\n");
    } else if (dev_type == acc_device_host) {
        printf("Host device type\n");
    } else {
        printf("Unknown device type\n");
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