#include "acc_testsuite.h"
#include <openacc.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef T1
// Test1: Checks the device_num directive 
int test1(){
    int err = 0;
    srand(SEED);
    int device_count = acc_get_num_devices(acc_device_default);

    #pragma acc set device_num(rand() % device_count) 
    {
        if (acc_get_device_num(acc_device_default) >= device_count){
            err = 1;
        }
    }

    return err;
}
#endif

#ifndef T2
// Test2: Checks the device_type directive
int test2(){
    int err = 0;
    srand(SEED);

    acc_device_t device_type = acc_get_device_type();
    #pragma acc set device_type(device_type) 
    {
        if (acc_get_device_type() != device_type){
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

#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif

    return failcode;
}