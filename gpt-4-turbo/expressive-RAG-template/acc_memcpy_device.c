#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

// Assumed definition for the framework's constants - adapt as necessary
#define SEED 42
#define NUM_TEST_CALLS 5

#ifndef T1
//T1:acc_memcpy_device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    // Define the size of the array to copy
    size_t num_elements = 1024;
    size_t bytes = num_elements * sizeof(float);
    
    // Allocate memory on the device for source and destination
    float* data_dev_src = (float*)acc_malloc(bytes);
    float* data_dev_dest = (float*)acc_malloc(bytes);
    
    // Check if memory allocation was successful
    if (!data_dev_src || !data_dev_dest) {
        fprintf(stderr, "Failed to allocate memory on the device.\n");
        return 1;  // Memory allocation error
    }
    
    // Initialize the source array on the host
    float* host_src = (float*)malloc(bytes);
    for (size_t i = 0; i < num_elements; ++i) {
        host_src[i] = (float)rand() / RAND_MAX;
    }

    // Copy the host array to the device source array
    acc_memcpy_to_device(data_dev_src, host_src, bytes);
    
    // Perform the device-to-device copy
    acc_memcpy_device(data_dev_dest, data_dev_src, bytes);
    
    // Retrieve the destination array back to the host for verification
    float* host_dest = (float*)malloc(bytes);
    acc_memcpy_from_device(host_dest, data_dev_dest, bytes);
    
    // Verify the correctness of the copy operation
    for (size_t i = 0; i < num_elements; ++i) {
        if (host_dest[i] != host_src[i]) {
            err = 1;  // Data did not match, copy operation failed
            break;
        }
    }
    
    // Cleanup resources
    free(host_src);
    free(host_dest);
    acc_free(data_dev_src);
    acc_free(data_dev_dest);
    
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
        printf("Test failed.\n");
    } else {
        printf("Test passed.\n");
    }
#endif
    return failcode;
}