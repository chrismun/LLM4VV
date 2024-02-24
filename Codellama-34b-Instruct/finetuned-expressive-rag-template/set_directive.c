#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:set directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int device_type = acc_get_device_type();
    int device_num = acc_get_device_num(device_type);
    int default_async = acc_get_default_async();

    #pragma acc set device_type(device_type)
    #pragma acc set device_num(device_num)
    #pragma acc set default_async(default_async)

    int new_device_type = acc_get_device_type();
    int new_device_num = acc_get_device_num(new_device_type);
    int new_default_async = acc_get_default_async();

    if (new_device_type != device_type || new_device_num != device_num || new_default_async != default_async) {
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