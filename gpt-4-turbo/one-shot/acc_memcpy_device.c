#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <openacc.h>

#define SEED 12345
#define n 1024
#define PRECISION 0.001

int test_acc_memcpy_device() {
    int err = 0;
    srand(SEED);
    float *host_a = (float *)malloc(n * sizeof(float));
    float *host_b = (float *)malloc(n * sizeof(float));
    float *device_a;

    // Initialize host array
    for (int i = 0; i < n; ++i) {
        host_a[i] = (float)rand() / RAND_MAX;
        host_b[i] = -1.0; // Initialize with a different value to check copy
    }

    // Allocate device memory
    device_a = (float *)acc_malloc(n * sizeof(float));

    // Copy data from host to device
    acc_memcpy_to_device(device_a, host_a, n * sizeof(float));

    // Use OpenACC parallel directive to modify the data on the device
    #pragma acc parallel present(device_a)
    {
        #pragma acc loop
        for(int i = 0; i < n; i++){
            device_a[i] = device_a[i] * 2.0f; // Example operation
        }
    }
    
    // Copy modified data back from device to host_b array
    acc_memcpy_from_device(host_b, device_a, n * sizeof(float));
    
    // Verify the data is correctly modified and copied back
    for (int i = 0; i < n; ++i) {
        if (fabs(2.0f * host_a[i] - host_b[i]) > PRECISION) {
            err += 1;
        }
    }

    // Release device memory
    acc_free(device_a);

    // Cleanup host memory
    free(host_a);
    free(host_b);

    return err;
}

int main() {
    int fail = test_acc_memcpy_device();

    if(fail == 0) {
        printf("ACC memcpy device test PASSED\n");
    } else {
        printf("ACC memcpy device test FAILED with %d errors\n", fail);
    }

    return fail;
}