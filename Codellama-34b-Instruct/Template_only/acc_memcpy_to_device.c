#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device memory region
    acc_device_t device = acc_get_device();
    acc_device_memory_t device_memory = acc_malloc(device, sizeof(int));

    // Copy data to the device memory region
    int data = 1234;
    acc_memcpy(device_memory, &data, sizeof(int));

    // Verify that the data was copied correctly
    int result = 0;
    acc_memcpy(&result, device_memory, sizeof(int));
    if (result != data) {
        err = 1;
    }

    // Free the device memory region
    acc_free(device_memory);

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