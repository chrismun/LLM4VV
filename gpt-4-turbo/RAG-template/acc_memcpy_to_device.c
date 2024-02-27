#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include <string.h> // for memcmp

#define SEED 12345
#define NUM_ELEMENTS 1024

// Helper function to check if two arrays are equal
int array_equals(int* a, int* b, size_t n) {
    for (size_t i = 0; i < n; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

int test_acc_memcpy_to_device(){
    int err = 0;
    srand(SEED);

    size_t bytes = NUM_ELEMENTS * sizeof(int);

    // Allocate and initialize an array on the host
    int *data_host_src = (int*) malloc(bytes);
    for(int i = 0; i < NUM_ELEMENTS; i++) {
        data_host_src[i] = rand();
    }

    // Allocate memory on the device
    int *data_dev_dest = (int*) acc_malloc(bytes);
    if (data_dev_dest == NULL) {
        fprintf(stderr, "Error allocating device memory.\n");
        free(data_host_src);
        return 1;
    }

    // Copy data from host to device
    acc_memcpy_to_device(data_dev_dest, data_host_src, bytes);

    // Allocate and initialize a different array to copy back the device data
    int *data_host_dest = (int*) malloc(bytes);

    // Copy data from device back to a new host array for verification
    acc_memcpy_from_device(data_host_dest, data_dev_dest, bytes);

    // Verify the contents of the device and host arrays match
    if (!array_equals(data_host_src, data_host_dest, NUM_ELEMENTS)) {
        fprintf(stderr, "Data verification failed: host and device arrays do not match.\n");
        err = 1;
    }

    // Cleanup
    acc_free(data_dev_dest);
    free(data_host_src);
    free(data_host_dest);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = test_acc_memcpy_to_device();
    if (failed != 0){
        failcode = 1;
    }

    if (failcode == 0) {
        printf("Test passed.\n");
    } else {
        printf("Test failed.\n");
    }

    return failcode;
}