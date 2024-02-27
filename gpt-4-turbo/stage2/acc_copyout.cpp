#include <iostream>
#include <cstdlib>
#include <cstring>

// Define a constant for the size of the array
#define ARRAY_SIZE 100
#define SEED 42
#define NUM_TEST_CALLS 10

int test_copyout(){
    int err = 0;
    srand(SEED);

    // Host and device arrays
    int *host_array = new int[ARRAY_SIZE];
    int *device_array;

    // Zero-initialize host array to ensure it's all zeros before copying back
    memset(host_array, 0, ARRAY_SIZE * sizeof(int));

    // Allocate memory on the device
    #pragma acc enter data create(device_array[0:ARRAY_SIZE])

    // Initialize the device array
    #pragma acc parallel loop present(device_array)
    for (int i = 0; i < ARRAY_SIZE; ++i){
        device_array[i] = rand() % 100; // Initialize with some random data
    }

    // Copy data back to host
    #pragma acc exit data copyout(device_array[0:ARRAY_SIZE])

    // Testing if the data is correctly copied back to host
    // Here we simply test if host_array is non-zero, as we initialized device array with non-zero values
    for (int i = 0; i < ARRAY_SIZE; ++i){
        if (host_array[i] == 0){ // If any element is zero, copyout failed
            err = 1; // Indicate an error
            break;
        }
    }

    // Cleanup
    delete[] host_array;

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_copyout();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}