#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

// Use a macro to control verbose output for debugging
#define VERBOSE 0

int test_shutdown(){
    int err = 0;
    float *host_array, *device_array;
    size_t num_elements = 1024;
    size_t bytes = num_elements * sizeof(float);

    host_array = (float *)malloc(bytes);

    // Initialize host array
    for (size_t i = 0; i < num_elements; i++) {
        host_array[i] = i;
    }
    
    // Allocate and copy to device memory
    #pragma acc enter data copyin(host_array[0:num_elements])

    // Perform some operations on the device
    #pragma acc parallel loop present(host_array[0:num_elements])
    for (size_t i = 0; i < num_elements; ++i) {
        host_array[i] = host_array[i] * 2.0f;
    }

    // Shutdown device of type acc_device_default
    acc_shutdown(acc_device_default);

    // Attempt to perform operations after shutdown
    #pragma acc enter data copyin(host_array[0:num_elements]) if(0) // Expected to not execute because of shutdown
    #pragma acc parallel loop present(host_array[0:num_elements]) if(0) // Expected to not execute
    for (size_t i = 0; i < num_elements; ++i) {
        host_array[i] = host_array[i] + 1.0f;
    }
    
    // Check if operations after shutdown did not happen
    for (size_t i = 0; i < num_elements; ++i) {
        if (host_array[i] != i * 2.0f) {
            err++;
            if (VERBOSE) {
                printf("Error: Data modified after shutdown at index %zu\n", i);
            }
            break;
        }
    }

    free(host_array);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = test_shutdown();
    
    if (failed != 0){
        failcode += 1;
    }

    if (failcode == 0) {
        printf("ACC Shutdown test passed.\n");
    } else {
        printf("ACC Shutdown test failed with %d errors.\n", failcode);
    }

    return failcode;
}