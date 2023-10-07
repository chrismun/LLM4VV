#include "acc_testsuite.h"

#ifndef DATA_DEVICEPTR_TEST
#define DATA_DEVICEPTR_TEST

int data_deviceptr_test() {
    int err = 0;
    int n = 10000;
    int *device_data;
    
    device_data = (int*)acc_malloc(n * sizeof(int));
    
    // Initialize data on the device
    #pragma acc parallel loop deviceptr(device_data)
    for (int i = 0; i < n; ++i){
        device_data[i] = i;
    }

    // Check the values on the host
    #pragma acc data deviceptr(device_data)
    {
        #pragma acc parallel loop reduction(+:err)
        for (int i = 0; i < n; ++i){
            if (device_data[i] != i)
                err++;
        }
    }

    acc_free(device_data);
    
    return err;
}

#endif

int main() {
    int failcode = 0;
    int failed;
    // Run the test
    failed = data_deviceptr_test();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}