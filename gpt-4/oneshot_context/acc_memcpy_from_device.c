#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SIZE 100

int main() {
    // Allocate host memory
    float* host_x = (float*) malloc(SIZE * sizeof(float));

    // Allocate device memory
    float* dev_x = (float*) acc_malloc(SIZE * sizeof(float));

    if (!dev_x) {
        printf("Device memory allocation failed!\n");
        exit(1);
    }

    // Initialize device memory
    #pragma acc parallel loop deviceptr(dev_x)
    for (int i = 0; i < SIZE; ++i) {
        dev_x[i] = i * 1.0f;
    }

    // Copy data from device to host
    acc_memcpy_from_device(host_x, dev_x, SIZE * sizeof(float));

    // Print data on the host for verification
    for (int i = 0; i < SIZE; ++i) {
        printf("host_x[%d] = %f\n", i, host_x[i]);
    }

    // Cleanup device and host memory
    acc_free(dev_x);
    free(host_x);

    return 0;