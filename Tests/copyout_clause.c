#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TEST_CALLS 100
#define SEED 12345

int test1() {
    int err = 0;
    srand(SEED);

    // Generate random data
    int data[10];
    for (int i = 0; i < 10; i++) {
        data[i] = rand();
    }

    // Copy data to device
    int *dev_data;
    cudaMalloc((void **)&dev_data, 10 * sizeof(int));
    cudaMemcpy(dev_data, data, 10 * sizeof(int), cudaMemcpyHostToDevice);

    // Copy data back to host
    int *host_data;
    cudaMallocHost((void **)&host_data, 10 * sizeof(int));
    cudaMemcpy(host_data, dev_data, 10 * sizeof(int), cudaMemcpyDeviceToHost);

    // Verify that data has been copied correctly
    for (int i = 0; i < 10; i++) {
        if (host_data[i] != data[i]) {
            err = 1;
            break;
        }
    }

    // Free device and host memory
    cudaFree(dev_data);
    cudaFreeHost(host_data);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif

    return failcode;
}