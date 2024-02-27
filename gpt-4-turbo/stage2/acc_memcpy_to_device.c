#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include <string.h> // For memcmp

// Assuming a predefined constant for seed and number of test calls
#define SEED 12345
#define NUM_TEST_CALLS 10

// Utility function for generating test data
void generateTestData(float *data, size_t num_elements) {
    for (size_t i = 0; i < num_elements; ++i) {
        data[i] = rand() / (float)RAND_MAX;
    }
}

// Test function for acc_memcpy_to_device
int test1(){
    int err = 0;
    srand(SEED);
    const size_t num_elements = 1024;
    size_t bytes = num_elements * sizeof(float);
    
    // Host and device memory allocation
    float *host_data = (float*)malloc(bytes);
    float *device_data = (float*)acc_malloc(bytes);
    float *host_data_copy = (float*)malloc(bytes);

    if (host_data == NULL || device_data == NULL || host_data_copy == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1; // Memory allocation failure is considered an error in test
    }

    // Generate test data
    generateTestData(host_data, num_elements);

    // Copy data to device
    acc_memcpy_to_device(device_data, host_data, bytes);

    // Copy data back to a different host array to verify
    acc_memcpy_from_device(host_data_copy, device_data, bytes);

    // Verify the copied data
    if (memcmp(host_data, host_data_copy, bytes) != 0) {
        fprintf(stderr, "Data verification failed. The copied data does not match the original data.\n");
        err = 1; // Data mismatch
    }

    // Cleanup
    free(host_data);
    acc_free(device_data);
    free(host_data_copy);

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    
    if (failed != 0){
        failcode |= (1 << 0);
    }

    return failcode;
}