#include "acc_testsuite.h"
#include <openacc.h>

#ifndef T1
// Test for acc_get_device_num
int test1(){
    int err = 0;
    srand(SEED);

    int dev_type = acc_get_device_type();
    int actual_device_num = acc_get_device_num(dev_type);
    
    acc_set_device_num(actual_device_num + 1, dev_type);
    int new_device_num = acc_get_device_num(dev_type);

    if(new_device_num == actual_device_num || new_device_num != actual_device_num + 1){
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