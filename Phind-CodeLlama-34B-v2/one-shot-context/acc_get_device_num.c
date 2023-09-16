#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1

int test_acc_get_device_num(){
    int err = 0;
    int device_type = acc_get_device_type();
    int device_num = acc_get_device_num(device_type);

    if(device_num == -1){
        printf("No devices of type %d found or type not supported\n", device_type);
        err = 1;
    }
    else{
        printf("Device number for device type %d: %d\n", device_type, device_num);
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_acc_get_device_num();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}