#include <iostream>
#include <stdlib.h>
#include <openacc.h>
#include <cstring>
// To define testing constants like SEED and NUM_TEST_CALLS, an additional header is presumed
// If it doesn't exist, define them directly for simplicity.
#ifndef ACC_TESTSUITE_H
#define SEED 123
#define NUM_TEST_CALLS 10
#endif

#ifndef T1
//T1:acc_memcpy_d2d,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize data
    const size_t bytes = 1024; // Define the size of the data to copy
    int *src_data = static_cast<int*>(acc_malloc(bytes)); // Allocate memory on the device
    int *dest_data = static_cast<int*>(acc_malloc(bytes)); // Allocate memory on another location on the device
    if (!src_data || !dest_data) {
        std::cerr << "Memory allocation error.\n";
        return 1; // Return non-zero if memory allocation failed
    }
    
    // Initialize src_data with random values
    int host_data[bytes / sizeof(int)]; // Host array to initialize device memory
    for (size_t i = 0; i < bytes / sizeof(int); ++i) {
        host_data[i] = std::rand(); // Populate with random values
    }
    acc_memcpy_h2d(src_data, host_data, bytes); // Copy data from host to device src_data
    
    // Perform acc_memcpy_d2d from src_data to dest_data
    int current_device = acc_get_device_num(acc_get_device_type());
    acc_memcpy_d2d(dest_data, src_data, bytes, current_device, current_device);
    
    // Copy data back to host to verify
    int verify_data[bytes / sizeof(int)];
    acc_memcpy_d2h(verify_data, dest_data, bytes);
    
    // Verify the copied data
    for (size_t i = 0; i < bytes / sizeof(int); ++i) {
        if (host_data[i] != verify_data[i]) {
            err = 1; // Set error flag if any value does not match
            break;
        }
    }
    
    // Free allocated memory on device
    acc_free(src_data);
    acc_free(dest_data);
    
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