#include "acc_testsuite.h"
#ifndef T1
//T1:set directive,V:2.7-3.3
int test1(){
    int err = 0;
    int device_type = acc_device_default;
    int device_num = 1;
    int async_mode = acc_async_default;

    #pragma acc set device_type(device_type) device_num(device_num) default_async(async_mode)

    if (acc_get_device_type() != device_type) {
        err += 1;
    }

    if (acc_get_device_num() != device_num) {
        err += 1;
    }

    if (acc_get_default_async() != async_mode) {
        err += 1;
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