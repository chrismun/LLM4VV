#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,loop,V:2.5-2.9
int test1(){
    int err = 0;

    int device_id = acc_get_device_type();
    if(device_id != acc_device_none){
        err += 1;
    }

    #pragma acc parallel
    {
        int device_id = acc_get_device_type();
        if(device_id != acc_device_gpu){
            err += 1;
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