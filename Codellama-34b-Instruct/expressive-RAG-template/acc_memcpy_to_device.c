#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device memory region
    acc_device_t device = acc_get_device();
    acc_device_memory_t device_mem = acc_malloc(device, sizeof(int) * 10);

    // Copy data from host to device
    int* host_data = (int*)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        host_data[i] = i;
    }
    acc_memcpy(device_mem, host_data, sizeof(int) * 10);

    // Verify that the data was copied correctly
    int* device_data = (int*)acc_device_memory_get_pointer(device_mem);
    for (int i = 0; i < 10; i++) {
        if (device_data[i] != host_data[i]) {
            err = 1;
            break;
        }
    }

    // Free device memory
    acc_free(device_mem);

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