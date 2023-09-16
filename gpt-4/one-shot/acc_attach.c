#include <openacc.h>
#include <stdlib.h>
#include <assert.h>
#include "acc_testsuite.h"

int test() {
    int err = 0;

    unsigned int length = 10000;
    float *host_memory = (float*) malloc(length * sizeof(float));

    #pragma acc enter data create(host_memory[0:length])

    // Initialize device side memory
    #pragma acc parallel loop present(host_memory[0:length])
    for (int i = 0; i < length; i++){
        host_memory[i] = i * 1.0f;
    }

    float *device_memory;
    #pragma acc data deviceptr(device_memory)
    {
        device_memory = acc_deviceptr(host_memory);
        assert(device_memory != NULL);

        #pragma acc attach(deviceptr(device_memory))

        // Validate
        #pragma acc parallel loop present(device_memory[0:length])
        for (int i = 0; i < length; i++){
            if (device_memory[i] != i * 1.0f) err++;
        }
    }
    
    #pragma acc exit data delete(host_memory[0:length])

    free(host_memory);

    return err;
}

int main() {
    int failcode = 0;
    int failed;
    
    failed = 0;
    for (int i = 0; i < NUM_TEST_CALLS; i++){
        failed += test();
    }
    if (failed != 0){
        failcode |= (1 << 0);
    }
    
    return failcode;
}