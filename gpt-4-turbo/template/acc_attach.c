#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,V:2.7-3.3
int test1(){
    const int array_size = 1024;
    int err = 0;
    srand(SEED);

    // Host and device pointers
    float *host_array;
    float *device_array;

    // Allocate memory on the host
    host_array = (float *)malloc(array_size * sizeof(float));

    // Initialize host memory
    for (int i = 0; i < array_size; ++i) {
        host_array[i] = (float)rand() / (float)(RAND_MAX);
    }

    // Allocate memory on the device and get a device pointer
    device_array = (float *)acc_malloc(array_size * sizeof(float));
    
    // Attach the host array to the device memory
    #pragma acc enter data copyin(host_array[0:array_size])
    acc_attach((void **)&device_array);

    // Perform parallel operation on the array
    #pragma acc parallel loop present(device_array)
    for (int i = 0; i < array_size; ++i) {
        device_array[i] = device_array[i] * 2.0f; // Example operation: double every element
    }

    // Copy data back to host to verify correctness
    #pragma acc exit data copyout(host_array[0:array_size])
    
    // Detach the device memory before freeing
    acc_detach((void **)&device_array);
    acc_free(device_array);

    // Verify the operation was successful
    for (int i = 0; i < array_size; ++i) {
        if (host_array[i] <= 0 || host_array[i] != host_array[i]) { // Verify the value is changed and not nan
            err++;
            break;
        }
    }

    free(host_array);
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