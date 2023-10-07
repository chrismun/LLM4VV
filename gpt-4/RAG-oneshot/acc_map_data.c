#include <openacc.h>
#include <malloc.h>
#include <stdio.h>

#define SIZE 1000 // Size of array

void printError() {
    const char *errMsg;
    size_t size;

    acc_get_last_error_message(&errMsg, &size);
    printf("ACC Error: %s \n", errMsg);
}

int main() {

    float *x = (float*) malloc(SIZE*sizeof(float));

    if(x == NULL) {
        printf("Host memory allocation failed.\n");
        return 1;
    }

    // Initializing data on host
    for(int i = 0; i < SIZE; ++i) {
        x[i] = i+1;
    }

    // Allocate device memory
    float *x_dev = (float*) acc_malloc(SIZE*sizeof(float));

    if(x_dev == NULL) {
        printf("Device memory allocation failed.\n");
        return 1;
    }

    // Map host memory to device memory
    acc_map_data(x, x_dev, SIZE*sizeof(float));

    // Check if memory mapping was successful
    if(acc_get_current_cuda_device() != acc_device_not_host && acc_is_present(x, SIZE*sizeof(float)) == 0) {
        printf("Data mapping to device memory unsuccessful.\n");
        return 1;
    } else {
        printf("Data mapped to device memory successfully.\n");
    }

    // Perform a simple copy operation
    #pragma acc parallel loop present(x)
    for(int i = 0; i < SIZE; ++i) {
        x_dev[i] = x[i];
    }

    // Unmap host memory from device memory
    acc_unmap_data(x);

    // Check whether unmap operation was successful
    if(acc_is_present(x, SIZE*sizeof(float)) != 0) {
        printf("Data unmap operation unsuccessful.\n");
        return 1;
    } else {
        printf("Data unmapped from device memory successfully.\n");
    }

    // Release device memory
    acc_free(x_dev);

    // Release host memory
    free(x);

    return 0;
}