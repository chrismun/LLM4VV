c
#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Test that the shutdown directive is executed only when the if clause is true.
    if(rand() % 2 == 0){
        err = 1;
    }

    // Test that the shutdown directive is executed only when the device type is available.
    if(acc_get_device_type() == acc_device_default){
        err = 1;
    }

    // Test that the shutdown directive is executed only when the device number is valid.
    if(acc_get_device_num() < 0 || acc_get_device_num() >= acc_get_num_devices()){
        err = 1;
    }

    // Test that the shutdown directive is executed only when the device is available.
    if(acc_get_device_state(acc_get_device_num()) != acc_device_available){
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