#include "acc_testsuite.h"

#ifndef T1
//T1:acc set device num,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if (acc_get_device_type() != acc_device_none){
        acc_set_device_type(acc_get_device_type_default);
        acc_set_device_num(acc_get_device_num(acc_get_device_type_default), acc_get_device_type_default);
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