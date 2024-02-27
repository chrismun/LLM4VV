#include "acc_testsuite.h"
#ifndef T1
//T1:acc set device type,V:2.7-3.3
int test1(){
    int err = 0;
    acc_device_t device_type = acc_get_device_type();
    cout << "Current device type: " << device_type << endl;
    acc_set_device_type(1);
    device_type = acc_get_device_type();
    if (device_type != 1){
        err += 1;
        cout << "Error setting device type: " << device_type << endl;
    }

    return err;
}

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