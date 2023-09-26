#include "acc_testsuite.h"
#ifndef T1
//T1:acc get device num,V:2.7-3.3
int test1(){
    int err = 0;
    int device_type = acc_get_device_type();
    int device_num = acc_get_device_num(device_type);

    if (device_num == -1) {
        err = 1;
        acc_set_device_num(device_type, 0);
        device_num = acc_get_device_num(device_type);
        if (device_num != 0) {
            err = 2;
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