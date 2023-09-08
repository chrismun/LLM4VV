#include "acc_testsuite.h"
#ifndef T1
//T1:compute construct self clause,V:2.7-3.3
int test1(){
    int err = 0;
    int device_type = acc_get_device_type();
    int device_num = acc_get_device_num(device_type);
    int host_device_num = acc_get_device_num(acc_device_host);

    if (device_type == acc_device_host) {
        // If the current device is the host, the self clause should execute on the local device
        #pragma acc parallel self(device_type != acc_device_host)
        {
            if (acc_get_device_type() != acc_device_host) {
                err = 1;
            }
        }
    } else {
        // If the current device is not the host, the self clause should execute on the current device
        #pragma acc parallel self(device_type == acc_device_host)
        {
            if (acc_get_device_type() != device_type || acc_get_device_num(device_type) != device_num) {
                err = 1;
            }
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