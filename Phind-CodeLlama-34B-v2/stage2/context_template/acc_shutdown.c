#include "acc_testsuite.h"
#ifndef T1
//T1:acc shutdown,V:2.7-3.3
int test1(){
    int err = 0;
    int device_type = acc_get_device_type();
    int device_num = acc_get_device_num(device_type);

    acc_init(device_type);
    acc_set_device_type(device_type);

    // Call acc_shutdown
    acc_shutdown(device_type);

    // Call acc_shutdown_device
    acc_init(device_type);
    acc_set_device_num(device_num, device_type);
    acc_shutdown_device(device_num, device_type);

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