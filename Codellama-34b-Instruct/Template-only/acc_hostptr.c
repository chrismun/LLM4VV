#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a host pointer to a data array
    int *data = (int *)malloc(sizeof(int) * 10);

    // Initialize the data array with random values
    for (int i = 0; i < 10; i++) {
        data[i] = rand();
    }

    // Create an OpenACC region and copy the data array to the device
    #pragma acc enter data copyin(data[:10])

    // Create a device pointer to the data array
    int *dev_data = (int *)acc_malloc(sizeof(int) * 10);

    // Copy the data array from the host to the device
    #pragma acc parallel loop present(data[:10])
    for (int i = 0; i < 10; i++) {
        dev_data[i] = data[i];
    }

    // Create a host pointer to the device data array
    int *host_data = (int *)acc_malloc(sizeof(int) * 10);

    // Copy the data array from the device to the host
    #pragma acc parallel loop present(dev_data[:10])
    for (int i = 0; i < 10; i++) {
        host_data[i] = dev_data[i];
    }

    // Check that the data array has been copied correctly
    for (int i = 0; i < 10; i++) {
        if (data[i] != host_data[i]) {
            err = 1;
            break;
        }
    }

    // Free the device memory
    #pragma acc exit data delete(dev_data[:10])

    // Free the host memory
    free(data);
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