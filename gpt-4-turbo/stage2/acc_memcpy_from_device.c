#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define N 100
#define SEED 42
#define NUM_TEST_CALLS 1

// Function to test acc_memcpy_from_device
int test_acc_memcpy_from_device() {
    int err = 0;
    int *host_array = (int*) malloc(N * sizeof(int));
    int *device_array;
    
    // Initialize device memory
    device_array = (int*) acc_malloc(N * sizeof(int));
    if (device_array == NULL) {
        fprintf(stderr, "Failed to allocate device memory.\n");
        return 1;
    }
    
    // Initialize data on device
    #pragma acc parallel loop deviceptr(device_array)
    for (int i = 0; i < N; i++) {
        device_array[i] = i;
    } 

    // Copy data from device to host
    acc_memcpy_from_device(host_array, device_array, N * sizeof(int));
    
    // Verify data
    for (int i = 0; i < N; i++) {
        if (host_array[i] != i) {
            printf("Data verification failed at element %d. Expected: %d, Found: %d\n", i, i, host_array[i]);
            err = 1;
            break;
        }
    }

    // Cleanup 
    acc_free(device_array);
    free(host_array);

    return err;
}

int main() {
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_acc_memcpy_from_device();
    }
    
    if (failed != 0) {
        failcode += 1;
        printf("Test failed.\n");
    } else {
        printf("Test passed.\n");
    }

    return failcode;
}