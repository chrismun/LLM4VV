#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

// Seed for srand to generate random values.
#define SEED 123
// Number of elements in the test array.
#define N 1024
// Number of times the test is run.
#define NUM_TEST_CALLS 10

int test_deviceptr(){
    int err = 0;
    srand(SEED);

    // Host allocation
    float *host_arr = (float *)malloc(N * sizeof(float));
    // Initialize host array with random values.
    for(int i = 0; i < N; ++i){
        host_arr[i] = (float)rand() / RAND_MAX;
    }
    
    // Allocate memory on the device and get the device pointer
    float *device_ptr;
    acc_device_t dev_type = acc_get_device_type();
    int dev_num = acc_get_device_num(dev_type);
    device_ptr = (float *)acc_malloc(N * sizeof(float));
    // Copy data from host to device explicitly (for demonstration)
    acc_memcpy_to_device(device_ptr, host_arr, N*sizeof(float));

    // Perform computation using deviceptr
    #pragma acc parallel loop deviceptr(device_ptr)
    for(int i = 0; i < N; ++i){
        device_ptr[i] += 1.0f; // Example operation: increment each element
    }

    // Copy result back to host array for verification
    acc_memcpy_from_device(host_arr, device_ptr, N*sizeof(float));

    // Verify the results
    for(int i = 0; i < N; ++i){
        if( host_arr[i] <= 1.0f ){ // since the original numbers are random and incremented by 1
            err++;
        }
    }

    // Cleanup
    acc_free(device_ptr);
    free(host_arr);

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_deviceptr();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    if (failcode == 0) {
        printf("Test Passed\n");
    } else {
        printf("Test Failed with %d errors\n", failed);
    }
    return failcode;
}