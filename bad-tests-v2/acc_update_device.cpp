#include <iostream>
#include <cstdlib>
#include <cstring>

#include "acc_testsuite.h"

// T1:acc update device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device memory region
    void* device_mem = acc_malloc(1024);
    if (device_mem == NULL) {
        std::cerr << "Failed to allocate device memory" << std::endl;
        return 1;
    }

    // Create a host memory region
    void* host_mem = malloc(1024);
    if (host_mem == NULL) {
        std::cerr << "Failed to allocate host memory" << std::endl;
        return 1;
    }

    // Initialize the host memory
    for (int i = 0; i < 1024; i++) {
        host_mem[i] = i;
    }

    // Copy the host memory to the device memory
    acc_update_device(host_mem, 1024);

    // Check that the device memory has been updated
    for (int i = 0; i < 1024; i++) {
        if (device_mem[i] != host_mem[i]) {
            std::cerr << "Device memory not updated correctly" << std::endl;
            err = 1;
            break;
        }
    }

    // Update the device memory from the host memory
    acc_update_self(device_mem, 1024);

    // Check that the host memory has been updated
    for (int i = 0; i < 1024; i++) {
        if (host_mem[i] != device_mem[i]) {
            std::cerr << "Host memory not updated correctly" << std::endl;
            err = 1;
            break;
        }
    }

    // Free the device and host memory
    acc_free(device_mem);
    free(host_mem);

    return err;
}

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