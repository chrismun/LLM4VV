#include <iostream>
#include <stdlib.h>
#include <openacc.h>
#include <cstring> // for memcmp

#ifndef SEED
#define SEED 12345 // A defined seed for reproducibility, can be replaced or overridden
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10 // Defines how many times to call the test for robust testing
#endif

// Test function for verifying acc_memcpy_device
int test_acc_memcpy_device(){
    int err = 0;
    srand(SEED);

    const size_t bytes = 1024; // Size of memory to be copied
    char* host_src = new char[bytes];
    char* host_dst = new char[bytes];
    
    // Initialize source with random data
    for(size_t i = 0; i < bytes; ++i) {
        host_src[i] = rand() % 256;
    }
    
    // Allocate memory on the device
    char* device_src = (char*) acc_malloc(bytes);
    char* device_dst = (char*) acc_malloc(bytes);
    
    // Copy host source data to device source memory
    acc_memcpy_to_device(device_src, host_src, bytes);
    
    // Perform the device-to-device memory copy
    acc_memcpy_device(device_dst, device_src, bytes);
    
    // Copy the data back to host destination for verification
    acc_memcpy_from_device(host_dst, device_dst, bytes);
    
    // Verify the copied data
    if (memcmp(host_src, host_dst, bytes) != 0) {
        std::cerr << "Error: Memory data mismatch detected." << std::endl;
        err = 1;
    }
    
    // Free allocated memory
    acc_free(device_src);
    acc_free(device_dst);
    delete[] host_src;
    delete[] host_dst;
    
    return err;
}

int main(){
    int failcode = 0;

    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        if (test_acc_memcpy_device() != 0){
            failcode = 1;
            std::cerr << "Test failed on iteration: " << x << std::endl;
            break; // Exit the loop on first failure
        }
    }

    if (failcode == 0) {
        std::cout << "All tests passed successfully." << std::endl;
    } else {
        std::cerr << "Some tests have failed." << std::endl;
    }
    
    return failcode;
}