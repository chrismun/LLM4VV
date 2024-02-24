#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1
#define SEED 123

int test1(){
    int err = 0;
    srand(SEED);

    int device_type = acc_get_device_type();
    int device_num = acc_get_device_num(device_type);

    #pragma acc init device_type(device_type) device_num(device_num)

    if (acc_get_device_type() != device_type || acc_get_device_num(device_type) != device_num){
        err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}