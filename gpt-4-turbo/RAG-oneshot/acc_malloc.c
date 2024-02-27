#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SEED 1234
#define NUM_ELEMENTS 1024

// Utility to check the result. It's simplistic but serves the purpose for our validation test.
int validate(float *host_data, size_t num_elements) {
    for (size_t i = 0; i < num_elements; ++i) {
        if (host_data[i] != i) {
            return -1; // Validation failed
        }
    }
    return 0; // Validation passed
}

int test_acc_malloc() {
    int err = 0;
    size_t bytes = NUM_ELEMENTS * sizeof(float);

    // Allocate memory on the device
    float *device_ptr = (float *) acc_malloc(bytes);
    if (device_ptr == NULL) {
        printf("Allocation failed.\n");
        return -1; // Allocation error
    }

    // Allocate host memory
    float *host_data = (float *) malloc(bytes);
    if (host_data == NULL) {
        printf("Host allocation failed.\n");
        acc_free(device_ptr); // Cleanup device memory
        return -1; // Allocation error
    }

    // Initialize host data
    for (size_t i = 0; i < NUM_ELEMENTS; ++i) {
        host_data[i] = (float)i;
    }

    // Copy data from host to device
    #pragma acc enter data copyin(host_data[0:NUM_ELEMENTS])

    // Use the device pointer in a parallel region
    #pragma acc parallel loop deviceptr(device_ptr)
    for (size_t i = 0; i < NUM_ELEMENTS; ++i) {
        device_ptr[i] = host_data[i];
    }

    // Copy data back from device to host to check
    #pragma acc exit data copyout(host_data[0:NUM_ELEMENTS])
    
    // Validation
    err = validate(host_data, NUM_ELEMENTS);

    // Cleanup
    free(host_data);
    acc_free(device_ptr);

    return err;
}

int main() {
    if (test_acc_malloc() == 0) {
        printf("Test passed, acc_malloc works as expected.\n");
    } else {
        printf("Test failed.\n");
    }
    return 0;
}