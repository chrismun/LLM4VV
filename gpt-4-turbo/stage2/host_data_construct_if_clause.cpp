#include <cstdlib>
#include <iostream>
#include <openacc.h>

#define SEED 123
#define NUM_TEST_CALLS 1

// Sample test function to evaluate the host_data construct if clause
int test1(){
    int err = 0;
    srand(SEED);
    
    const int size = 1;
    float host_array[size] = {0.0f};
    bool condition = true; // Set to true; the construct should work.
    
    // Allocate device memory
    float* device_ptr = static_cast<float*>(acc_malloc(size * sizeof(float)));
    if (!device_ptr) {
        std::cerr << "Failed to allocate device memory." << std::endl;
        return 1;
    }

    host_array[0] = 5.0f; // Setting a known value to check if transfer occurs

    // Expected to replace the address if the condition is true
    #pragma acc host_data use_device(device_ptr) if(condition)
    {
        acc_memcpy_to_device(device_ptr, host_array, size * sizeof(float));
    }

    // Reset host_array to detect successful copy
    host_array[0] = 0.0f;
    
    // Copy back to verify
    #pragma acc host_data use_device(device_ptr)
    {
        acc_memcpy_from_device(host_array, device_ptr, size * sizeof(float));
    }
    
    // Check if the copy was successful
    if (host_array[0] != 5.0f) {
        err = 1; // If the data wasn't copied correctly, mark as error.
    }

    // Clean up
    acc_free(device_ptr);

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
    return failcode;
}