#include "acc_testsuite.h"
#include <stdlib.h>
#include <openacc.h>

#define SIZE 1024

// Function to allocate and initialize array on host
int* initialize_array() {
    int* array = (int*)malloc(SIZE * sizeof(int));
    for (int i = 0; i < SIZE; ++i) {
        array[i] = i;
    }
    return array;
}

// Test function that verifies if acc_hostptr is working correctly
int test_acc_hostptr(){
    int err = 0;
    srand(SEED);

    // Allocating and initializing an array on host
    int* host_array = initialize_array();

    //Moving the array to the device
    int* device_ptr = (int*)acc_copyin(host_array, SIZE * sizeof(int));

    // Getting the host pointer from device pointer
    int* host_ptr = (int*)acc_hostptr(device_ptr);

    // Comparing the original host pointer and the one obtained from acc_hostptr
    if (host_ptr != host_array){
        err = 1;
    }

    acc_delete(device_ptr, SIZE* sizeof(int));
    free(host_array);
    return err;
}

// Main function to call the test function
int main(){
    int failcode = 0;
    int failed;
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_acc_hostptr();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}