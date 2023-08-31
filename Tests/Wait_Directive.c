#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device buffer
    int *dev_buffer;
    cudaMalloc((void**)&dev_buffer, sizeof(int) * N);

    // Create a host buffer
    int *host_buffer;
    cudaMallocHost((void**)&host_buffer, sizeof(int) * N);

    // Initialize the host buffer
    for (int i = 0; i < N; i++) {
        host_buffer[i] = i;
    }

    // Copy the host buffer to the device buffer
    cudaMemcpy(dev_buffer, host_buffer, sizeof(int) * N, cudaMemcpyHostToDevice);

    // Launch the kernel
    kernel<<<1, N>>>(dev_buffer);

    // Wait for the kernel to complete
    cudaDeviceSynchronize();

    // Check if the device buffer contains the correct values
    for (int i = 0; i < N; i++) {
        if (dev_buffer[i] != i) {
            err = 1;
        }
    }

    // Free the device and host buffers
    cudaFree(dev_buffer);
    cudaFreeHost(host_buffer);

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