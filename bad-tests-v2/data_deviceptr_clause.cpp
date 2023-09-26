#include "acc_testsuite.h"

#ifndef T1
//T1:data deviceptr clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Declare a device pointer
    int* device_ptr = (int*)acc_malloc(sizeof(int));

    // Initialize the device pointer
    *device_ptr = 123;

    // Declare a host pointer
    int* host_ptr = (int*)malloc(sizeof(int));

    // Initialize the host pointer
    *host_ptr = 456;

    // Use the device pointer to access the data on the device
    acc_attach(device_ptr);
    acc_deviceptr(device_ptr);
    acc_detach(device_ptr);

    // Use the host pointer to access the data on the host
    acc_attach(host_ptr);
    acc_deviceptr(host_ptr);
    acc_detach(host_ptr);

    // Check that the data was correctly accessed
    if (*device_ptr != 123 || *host_ptr != 456) {
        err = 1;
    }

    // Free the device and host pointers
    acc_free(device_ptr);
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