#include "acc_testsuite.h"
#include <openacc.h>

void acc_close_device(int device_num){
  #pragma acc shutdown device_num(device_num)
}

int test_shutdown_directive(){
    int err = 0, device_num;
    
    device_num = acc_get_device_num(acc_get_device_type());

    // Setup and create some data on device
    #pragma acc enter data create(device_num)

    // Shutdown connection
    acc_close_device(device_num);

    // Try to access the data
    #pragma acc update host(device_num)
    if (device_num != acc_get_device_num(acc_get_device_type())){
        err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_shutdown_directive();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}