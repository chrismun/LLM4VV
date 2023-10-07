#include "acc_testsuite.h"
#ifndef T1
//T1:init directive,V:2.7-3.3
int test1(){
    int err = 0;
    int device_type = acc_get_device_type();
    int device_num = acc_get_device_num(device_type);

    #pragma acc init device_type(device_type) device_num(device_num)

    int current_device_type = acc_get_device_type();
    int current_device_num = acc_get_device_num(current_device_type);

    if (current_device_type != device_type || current_device_num != device_num) {
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