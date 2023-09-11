#include "acc_testsuite.h"

#ifndef T1
//T1:host_data construct use_device clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device memory region
    int *device_data = (int *)acc_malloc(sizeof(int));

    // Create a host memory region
    int *host_data = (int *)malloc(sizeof(int));

    // Initialize the host memory region
    *host_data = 1234;

    // Use the host_data construct to specify that the device memory region should be used
    acc_host_data(device_data, host_data, sizeof(int));

    // Use the use_device clause to specify that the device memory region should be used
    acc_use_device(device_data, sizeof(int));

    // Check that the device memory region is being used
    if (*device_data != 1234){
        err = 1;
    }

    // Free the device memory region
    acc_free(device_data);

    // Free the host memory region
    free(host_data);

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