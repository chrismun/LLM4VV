#include "acc_testsuite.h"
#ifndef T1
//T1:acc set device type,V:2.7-3.3
int test1(){
    int err = 0;
    int devices_host = acc_get_device_type(acc_device_host);
    int devices_nvidia = acc_get_device_type(acc_device_nvidia);
    int devices_radeon = acc_get_device_type(acc_device_radeon);

    if (devices_host > 0) {
        acc_set_device_type(acc_device_host);
        if (acc_get_device_type() != acc_device_host) {
            err = 1;
        }
    }

    if (devices_nvidia > 0) {
        acc_set_device_type(acc_device_nvidia);
        if (acc_get_device_type() != acc_device_nvidia) {
            err = 1;
        }
    }

    if (devices_radeon > 0) {
        acc_set_device_type(acc_device_radeon);
        if (acc_get_device_type() != acc_device_radeon) {
            err = 1;
        }
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