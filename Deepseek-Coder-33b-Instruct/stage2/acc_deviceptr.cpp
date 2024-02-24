#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 100

int test1(){
    int err = 0;
    int *host_ptr = (int*)malloc(sizeof(int));
    *host_ptr = 10;

    // Get the device pointer associated with the host pointer
    int *device_ptr = acc_deviceptr(host_ptr);

    // Check if the device pointer is null
    if(device_ptr == NULL){
        err = 1;
    }

    // Check if the device pointer points to the same address as the host pointer
    if(device_ptr != host_ptr){
        err = 1;
    }

    // Check if the value at the device pointer is the same as the value at the host pointer
    if(*device_ptr != *host_ptr){
        err = 1;
    }

    free(host_ptr);

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