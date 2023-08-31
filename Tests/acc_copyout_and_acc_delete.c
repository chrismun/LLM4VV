#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_TEST_CALLS 100
#define SEED 1234

int test1() {
    int err = 0;
    srand(SEED);

    // Generate random data
    int data[100];
    for (int i = 0; i < 100; i++) {
        data[i] = rand() % 100;
    }

    // Copy data to device
    int *dev_data;
    cudaMalloc((void **)&dev_data, sizeof(int) * 100);
    cudaMemcpy(dev_data, data, sizeof(int) * 100, cudaMemcpyHostToDevice);

    // Copy data back to host
    int *host_data;
    cudaMallocHost((void **)&host_data, sizeof(int) * 100);
    cudaMemcpy(host_data, dev_data, sizeof(int) * 100, cudaMemcpyDeviceToHost);

    // Verify that data was copied correctly
    for (int i = 0; i < 100; i++) {
        if (host_data[i] != data[i]) {
            err = 1;
            break;
        }
    }

    // Delete device memory
    cudaFree(dev_data);

    // Delete host memory
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