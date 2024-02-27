#include <iostream>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 123
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// Test for acc_deviceptr
// T1: acc_deviceptr, V:2.7-3.3
int test_acc_deviceptr(){
    int err = 0;
    srand(SEED);

    const int size = 1024;
    float* host_array = new float[size];
    // Initialize host array
    for(int i = 0; i < size; ++i){
        host_array[i] = static_cast<float>(rand()) / RAND_MAX;
    }

    // Move data to device - ensures there is a device side copy for acc_deviceptr to find
    #pragma acc enter data copyin(host_array[0:size])

    // Fetch device pointer
    float* device_ptr = (float*) acc_deviceptr(host_array);
    if (device_ptr == NULL) {
        std::cerr << "acc_deviceptr returned NULL, indicating data is not present on the device." << std::endl;
        err++;
    } else if (device_ptr == host_array) {
        std::cerr << "acc_deviceptr returned host address instead of device address." << std::endl;
        err++;
    }

    // Cleanup
    #pragma acc exit data delete(host_array[0:size])
    delete[] host_array;

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_acc_deviceptr();
    }

    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    
    return failcode;
}