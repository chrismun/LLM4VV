#include "acc_testsuite.h"

#ifndef T1
//T1:host_data construct use_device clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device array
    int *device_array = (int *)acc_malloc(sizeof(int) * 10);

    // Create a host array
    int *host_array = (int *)malloc(sizeof(int) * 10);

    // Initialize the host array
    for (int i = 0; i < 10; i++) {
        host_array[i] = i;
    }

    // Copy the host array to the device array
    acc_memcpy(device_array, host_array, sizeof(int) * 10);

    // Use the device array in a compute construct
    #pragma acc parallel loop
    for (int i = 0; i < 10; i++) {
        device_array[i] = device_array[i] + 1;
    }

    // Copy the device array back to the host array
    acc_memcpy(host_array, device_array, sizeof(int) * 10);

    // Check the results
    for (int i = 0; i < 10; i++) {
        if (host_array[i] != i + 1) {
            err = 1;
            break;
        }
    }

    // Free the device array
    acc_free(device_array);

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