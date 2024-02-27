#include <iostream>
#include <openacc.h>
#include <cstdlib> // For srand(), rand()
#include <cstring> // For memcmp()

#define SEED 12345
#define NUM_TEST_CALLS 10

// Test acc_memcpy_from_device functionality
int test_memcpy_from_device() {
    int err = 0;
    srand(SEED);
    
    const size_t dataSize = 1024; // Size of data to be tested
    int hostArray[dataSize]; // Host array to copy data into
    int* deviceArray; // Device pointer for data source
    
    // Allocate memory on the device
    deviceArray = (int*)acc_malloc(dataSize * sizeof(int));
    if (!deviceArray) {
        std::cerr << "Device memory allocation failed." << std::endl;
        return 1;
    }
    
    // Initialize device memory with random data
    #pragma acc parallel loop present(deviceArray[0:dataSize])
    for (size_t i = 0; i < dataSize; i++) {
        deviceArray[i] = rand();
    }
    
    // Perform the memory copy from device to host
    acc_memcpy_from_device(hostArray, deviceArray, dataSize * sizeof(int));
    
    // Verify the data was copied correctly
    int temp[dataSize];
    #pragma acc update self(temp[0:dataSize]) // Copy data from deviceArray to temp for comparison
    err = memcmp(hostArray, temp, dataSize * sizeof(int)) != 0; // Compare hostArray and temp
    
    // Check for memcmp error
    if (err) {
        std::cerr << "Data verification failed: Memory comparison mismatch." << std::endl;
    }
    
    // Clean up
    acc_free(deviceArray);
    
    return err;
}

int main() {
    int failCode = 0;
    int failed = 0;
    
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed += test_memcpy_from_device();
    }
    
    if (failed != 0) {
        failCode |= (1 << 0); // Set first bit of failCode if any test failed
    }
    
    return failCode;
}