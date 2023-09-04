#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Set the device type to GPU
    acc_set_device_type(ACC_DEVICE_TYPE_GPU);

    // Create a data array on the device
    int *data = (int *)acc_malloc(sizeof(int) * 10);

    // Initialize the data array with random values
    for (int i = 0; i < 10; i++) {
        data[i] = rand();
    }

    // Set the device type to CPU
    acc_set_device_type(ACC_DEVICE_TYPE_CPU);

    // Create a data array on the device
    int *data_cpu = (int *)acc_malloc(sizeof(int) * 10);

    // Initialize the data array with random values
    for (int i = 0; i < 10; i++) {
        data_cpu[i] = rand();
    }

    // Compare the data arrays
    for (int i = 0; i < 10; i++) {
        if (data[i] != data_cpu[i]) {
            err = 1;
            break;
        }
    }

    // Free the data arrays
    acc_free(data);
    acc_free(data_cpu);

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