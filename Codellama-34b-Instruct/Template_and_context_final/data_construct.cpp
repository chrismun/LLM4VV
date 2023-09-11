#include "acc_testsuite.h"

#ifndef T1
//T1:data construct,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a new device memory space
    acc_device_t device = acc_get_device();
    acc_device_memory_t memory = acc_device_memory_create(device, 1024);

    // Allocate memory for the data
    acc_data_t data = acc_data_create(memory, 1024);

    // Copy data from local memory to device memory
    acc_data_copy(data, 0, 1024, 0, 1024);

    // Copy data from device memory to local memory
    acc_data_copy(data, 0, 1024, 0, 1024);

    // Free the device memory
    acc_device_memory_free(memory);

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