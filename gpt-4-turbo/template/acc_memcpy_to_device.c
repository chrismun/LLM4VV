#include "acc_testsuite.h"
#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    const int size = 1024; // Define the size of the array
    int *host_array = (int*)malloc(size * sizeof(int)); // Allocate memory for the host array
    int *device_array; // Pointer for the device array
    int *verification_array = (int*)malloc(size * sizeof(int)); // Array to copy back for verification

    // Initialize the host array with random data
    for (int i = 0; i < size; ++i){
        host_array[i] = rand();
    }

    // Allocate memory on the device
    device_array = (int *)acc_malloc(size * sizeof(int));
    if (device_array == NULL) {
        fprintf(stderr, "Failed to allocate device memory.");
        free(host_array);
        free(verification_array);
        return 1; // indicate error
    }

    // Copy from host to device
    acc_memcpy_to_device(device_array, host_array, size * sizeof(int));

    // For verification, copy from device to a new host array
    acc_memcpy_from_device(verification_array, device_array, size * sizeof(int));

    // Verify the arrays match
    for (int i = 0; i < size; ++i){
        if (host_array[i] != verification_array[i]){
            err++;
            break;
        }
    }

    // Free the allocated memory
    free(host_array);
    free(verification_array);
    acc_free(device_array);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}