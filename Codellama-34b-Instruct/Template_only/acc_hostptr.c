#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a host pointer to a data array
    int *host_ptr = (int *)malloc(sizeof(int) * 10);

    // Initialize the data array with random values
    for (int i = 0; i < 10; i++) {
        host_ptr[i] = rand();
    }

    // Create an OpenACC region and copy the data array to the device
    #pragma acc enter data copyin(host_ptr[:10])

    // Create a device pointer to the data array
    int *device_ptr = (int *)acc_malloc(sizeof(int) * 10);

    // Copy the data array from the host to the device
    #pragma acc parallel loop present(device_ptr[:10])
    for (int i = 0; i < 10; i++) {
        device_ptr[i] = host_ptr[i];
    }

    // Verify that the data array has been copied correctly
    #pragma acc parallel loop present(device_ptr[:10])
    for (int i = 0; i < 10; i++) {
        if (device_ptr[i] != host_ptr[i]) {
            err = 1;
            break;
        }
    }

    // Free the device memory
    #pragma acc exit data delete(device_ptr[:10])

    // Free the host memory
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