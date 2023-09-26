#include "acc_testsuite.h"
#ifndef T1
//T1:acc shutdown,V:2.7-3.3
int test1(){
    int err = 0;
    int device_type = acc_device_default;
    int device_num = 0;

    // Call acc_init to initialize the OpenACC environment
    acc_init(device_type);

    // Call acc_shutdown to shut down the connection to the device
    acc_shutdown(device_type);

    // Call acc_init again to initialize the OpenACC environment
    acc_init(device_type);

    // Call acc_shutdown_device to shut down the connection to the device_num
    acc_shutdown_device(device_num, device_type);

    // Call acc_init again to initialize the OpenACC environment
    acc_init(device_type);

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