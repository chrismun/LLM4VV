#include <openacc.h>
#include <stdio.h>
#include <stdlib.h>

// Function to run test case
int test_exit_data() {
    int error = 0;
    int num_elements = 1024;
    int *host_array = (int*)malloc(num_elements * sizeof(int));
    int *device_array;

    // Initialize host array
    for(int i=0; i<num_elements; i++){
        host_array[i] = i;
    }

    // Allocate memory on device
    #pragma acc enter data create(device_array[0:num_elements])

    // Copy host array to device array
    #pragma acc update device(device_array[0:num_elements] = host_array[0:num_elements])
  
    // Implemented some kind of computation using device_array on the device
    #pragma acc kernels
    for(int i=0; i<num_elements; i++){
        device_array[i] += i;
    }

    // Exit data: copy from device to host and deallocate on device
    #pragma acc exit data copyout(device_array[0:num_elements])

    // Check if changes are reflected to the host array
    for(int i=0; i<num_elements; i++){
        if (host_array[i] != device_array[i]) {
            error = 1;
            break;
        }
    }
    // Clean up
    free(host_array);

    return error;
}

int main(){
    int error;

    error = test_exit_data();

    if (error) {
        printf("Test failed\n");
        return EXIT_FAILURE;
    }
    else {
        printf("Test passed\n");
        return EXIT_SUCCESS;
    }
}