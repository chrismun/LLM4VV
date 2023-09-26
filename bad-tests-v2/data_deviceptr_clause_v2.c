#include "acc_testsuite.h"

#ifndef T1
//T1:data deviceptr clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Declare a device pointer
    int *device_ptr;

    // Allocate memory on the device
    device_ptr = (int *)acc_malloc(sizeof(int));

    // Set the device pointer to a random value
    *device_ptr = rand();

    // Declare a host pointer
    int *host_ptr;

    // Allocate memory on the host
    host_ptr = (int *)malloc(sizeof(int));

    // Set the host pointer to the same value as the device pointer
    *host_ptr = *device_ptr;

    // Use the data deviceptr clause to declare that the host pointer is a device pointer
    acc_data_deviceptr(host_ptr);

    // Use the data deviceptr clause to declare that the device pointer is a device pointer
    acc_data_deviceptr(device_ptr);

    // Use the data deviceptr clause to declare that the host pointer is a device pointer
    acc_data_deviceptr(host_ptr);

    // Use the data deviceptr clause to declare that the device pointer is a device pointer
    acc_data_deviceptr(device_ptr);

    // Check that the host pointer and device pointer have the same value
    if (*host_ptr != *device_ptr){
        err = 1;
    }

    // Free the memory on the device
    acc_free(device_ptr);

    // Free the memory on the host
    free(host_ptr);

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