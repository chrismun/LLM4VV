#include <iostream>
#include <openacc.h>
#include <cstdlib>

// Assuming acc_testsuite.h defines constants like SEED and NUM_TEST_CALLS
// For this example, we'll define them here for simplicity
#define SEED 123
#define NUM_TEST_CALLS 1

#ifndef T1
//T1:acc get property,V:2.7-3.3
int test1(){
    int err = 0;

    srand(SEED);

    // Ensuring a device is set to be used by OpenACC
    acc_init(acc_device_default);
    int dev_num = acc_get_device_num(acc_device_default);

    // Fetching the size of device memory
    size_t device_memory_size = acc_get_property(dev_num, acc_device_default, acc_property_memory);

    // Verifying the outcome
    if(device_memory_size == 0){
        // This might happen if the device doesn't support this property or is not accessible
        std::cerr << "Failed to retrieve device memory size." << std::endl;
        err = 1; // Indicate error
    } else {
        // Optional: Output fetched value for verification
        std::cout << "Device memory size: " << device_memory_size << " bytes" << std::endl;
    }

    // Finalizing OpenACC device use
    acc_shutdown(acc_device_default);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif

    return failcode;
}