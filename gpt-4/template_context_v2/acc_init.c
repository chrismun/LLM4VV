#include "acc_testsuite.h"
#include <openacc.h>

//T1:acc init, V:2.7-3.3
int test1() {
    int err = 0;
    
    int deviceNumBeforeInit = acc_get_device_num(acc_get_device_type());
    acc_init(acc_get_device_type());
    int deviceNumAfterInit = acc_get_device_num(acc_get_device_type());

    if(deviceNumBeforeInit != deviceNumAfterInit) {
        // The device number changed after acc_init() was called, which is unexpected.
        err = 1;
    }
    
    return err;
}

int main() {
    int failcode = 0;
    int failed;
    srand(0);

    failed = test1();

    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
    
    return failcode;
}