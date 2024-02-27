#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// Test function for validating acc_create behavior
int test_acc_create() {
    int err = 0;    
    size_t array_size = 1024; // Define the size of the array
    float* host_array = (float*) malloc(array_size * sizeof(float));
    
    // Initialize array with random values
    srand(SEED);
    for (size_t i = 0; i < array_size; ++i) {
        host_array[i] = (float)rand() / RAND_MAX;
    }
    
    // Use acc_create to allocate memory on the device and check pointer validity
    float* device_array = (float*) acc_create(host_array, array_size * sizeof(float));
    if (device_array == NULL) {
        fprintf(stderr, "acc_create failed to allocate device memory.\n");
        err++;
    }
    
    // Check if the host_array is present on the device using acc_is_present
    if (!acc_is_present(host_array, array_size * sizeof(float))) {
        fprintf(stderr, "Data is not present on the device as expected after acc_create.\n");
        err++;
    }

    // Cleanup
    acc_delete(host_array, array_size * sizeof(float));
    free(host_array);

    return err;
}

int main() {
    int failcode = 0;
    
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        if (test_acc_create() != 0) {
            failcode = 1;
            break;
        }
    }

    if (failcode) {
        printf("Test FAILED.\n");
    } else {
        printf("All tests PASSED.\n");
    }
    
    return failcode;
}