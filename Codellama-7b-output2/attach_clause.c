#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create an array with random values
    int arr[N];
    for (int i = 0; i < N; i++){
        arr[i] = rand();
    }

    // Create a device buffer to store the array
    int *dev_arr;
    cudaMalloc((void**)&dev_arr, N * sizeof(int));

    // Copy the array to the device buffer
    cudaMemcpy(dev_arr, arr, N * sizeof(int), cudaMemcpyHostToDevice);

    // Create an attach clause to specify that the device buffer should be attached to the device
    acc_attach(dev_arr, N * sizeof(int), cudaMemcpyDeviceToDevice);

    // Check that the attach clause has been applied correctly
    if (dev_arr != arr){
        err = 1;
    }

    // Free the device buffer
    cudaFree(dev_arr);

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