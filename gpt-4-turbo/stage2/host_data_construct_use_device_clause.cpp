#include <iostream>
#include <cstdlib> // for srand and rand
#include <openacc.h>

// Mock setup for demonstration, replace with your actual test suite and constants
const int SEED = 42;
const int NUM_TEST_CALLS = 5;

// Mock-up of a lower-level API function that would be using device pointers directly
void lower_level_api_using_device_ptr(int* device_ptr, int size) {
    // Example work that might be done by such a function, purely illustrative
    #pragma acc parallel loop
    for (int i = 0; i < size; ++i) {
        device_ptr[i] *= 2; // Pretend work done by a device-specific function
    }
}

// Test function for the use_device clause
int test1(){
    int err = 0;
    constexpr int size = 10;
    int *a = (int*)malloc(sizeof(int)*size); // Allocate array

    srand(SEED);
    for(int i = 0; i < size; ++i){
        a[i] = rand() % 100; // Initialize with random values
    }

    // Ensure data is present on the device
    #pragma acc enter data copyin(a[0:size])

    // Use the host_data construct to pass the device address to a lower-level API
    #pragma acc host_data use_device(a)
    {
        lower_level_api_using_device_ptr(a, size);
    }

    // Transfer data back to the host for verification
    #pragma acc exit data copyout(a[0:size])

    // Verify (simple check, replace with a more comprehensive verification logic if needed)
    for (int i = 0; i < size; ++i) {
        if (a[i] % 2 != 0) { // This simple check assumes the doubling should always result in even numbers
            err++;
        }
    }

    free(a); // Clean up dynamic memory
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode |= 1; // Bitwise OR to set fail bit
    }
    
    std::cout << "Test1 Failed Count: " << failed << std::endl;

    return failcode;
}