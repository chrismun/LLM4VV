#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device pointer
    int *device_ptr = (int *)acc_malloc(sizeof(int));

    // Set the device pointer to a random value
    *device_ptr = rand();

    // Create a host pointer
    int *host_ptr = (int *)malloc(sizeof(int));

    // Copy the device pointer to the host pointer
    acc_memcpy(host_ptr, device_ptr, sizeof(int));

    // Check if the host pointer contains the same value as the device pointer
    if (*host_ptr != *device_ptr){
        err = 1;
    }

    // Free the device pointer
    acc_free(device_ptr);

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