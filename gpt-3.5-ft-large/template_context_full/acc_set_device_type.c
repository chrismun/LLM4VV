#include "acc_testsuite.h"
#ifndef T1
//T1:acc set device type,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if (acc_get_device_type() != HOST){
        acc_set_device_type(acc_get_device_type() == HOST ? acc_device_none : acc_device_host);
        if (acc_get_device_type() != (HOST ? acc_device_none : acc_device_host)){
            err = 1;
        }
        acc_set_device_type((acc_get_device_type() & HOST) ? acc_device_host : acc_device_none);
        if (acc_get_device_type() != HOST){
            err = 1;
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