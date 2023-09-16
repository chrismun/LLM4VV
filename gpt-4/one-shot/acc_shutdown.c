#include "acc_testsuite.h"
#ifndef T1
//T1:init_shutdown,init_api,V:1.0-2.7
int test1(){
    int err = 0;
    int device_count;
    acc_device_t device_type;

    device_type = acc_get_device_type();
    device_count = acc_get_num_devices(device_type);

    for (int x = 0; x < device_count; ++x){
        acc_set_device_num(x, device_type);
        acc_init(device_type);

        if (acc_get_device_num(device_type) != x){
            err += 1;
        }

        acc_shutdown(device_type);
        if (acc_get_device_num(device_type) == x){
            err += 1;
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