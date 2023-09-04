#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a host pointer to a data array
    int *host_ptr = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        host_ptr[i] = i;
    }

    // Create an OpenACC device pointer to the same data array
    int *device_ptr = (int *)acc_malloc(sizeof(int) * 10);
    acc_memcpy_to_device(device_ptr, host_ptr, sizeof(int) * 10);

    // Use the OpenACC hostptr directive to specify that the host pointer is a device pointer
    #pragma acc hostptr(host_ptr)
    {
        // Use the device pointer to perform a computation on the data array
        #pragma acc parallel loop
        for (int i = 0; i < 10; i++) {
            host_ptr[i] = host_ptr[i] + 1;
        }
    }

    // Check that the data array has been updated correctly
    for (int i = 0; i < 10; i++) {
        if (host_ptr[i] != i + 1) {
            err = 1;
            break;
        }
    }

    // Free the device pointer and host pointer
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