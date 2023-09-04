#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Set the device type to GPU
    acc_set_device_type(ACC_DEVICE_TYPE_GPU);

    // Allocate memory on the device
    int *a = (int *)acc_malloc(sizeof(int));
    int *b = (int *)acc_malloc(sizeof(int));

    // Set the device type to CPU
    acc_set_device_type(ACC_DEVICE_TYPE_CPU);

    // Allocate memory on the device
    int *c = (int *)acc_malloc(sizeof(int));
    int *d = (int *)acc_malloc(sizeof(int));

    // Set the device type to GPU
    acc_set_device_type(ACC_DEVICE_TYPE_GPU);

    // Copy data from host to device
    acc_memcpy(a, &x, sizeof(int));
    acc_memcpy(b, &y, sizeof(int));

    // Set the device type to CPU
    acc_set_device_type(ACC_DEVICE_TYPE_CPU);

    // Copy data from host to device
    acc_memcpy(c, &z, sizeof(int));
    acc_memcpy(d, &w, sizeof(int));

    // Set the device type to GPU
    acc_set_device_type(ACC_DEVICE_TYPE_GPU);

    // Launch the kernel
    acc_launch(kernel, a, b, c, d);

    // Set the device type to CPU
    acc_set_device_type(ACC_DEVICE_TYPE_CPU);

    // Launch the kernel
    acc_launch(kernel, c, d, a, b);

    // Set the device type to GPU
    acc_set_device_type(ACC_DEVICE_TYPE_GPU);

    // Free memory on the device
    acc_free(a);
    acc_free(b);

    // Set the device type to CPU
    acc_set_device_type(ACC_DEVICE_TYPE_CPU);

    // Free memory on the device
    acc_free(c);
    acc_free(d);

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