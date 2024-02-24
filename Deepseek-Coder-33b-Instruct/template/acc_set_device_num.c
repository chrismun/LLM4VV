#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define T1
#include "acc_testsuite.h"

int test1(){
    int err = 0;
    int num_devices = acc_get_num_devices(acc_device_nvidia);

    if(num_devices < 1){
        printf("No NVIDIA devices found.\n");
        err = 1;
    }

    for(int i = 0; i < num_devices; i++){
        acc_set_device_num(i, acc_device_nvidia);
        if(acc_get_device_num(acc_device_nvidia) != i){
            printf("Device number mismatch. Expected: %d, Actual: %d\n", i, acc_get_device_num(acc_device_nvidia));
            err = 1;
        }
    }

    return err;
}

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