#include "acc_testsuite.h"

#ifndef T1
//T1:acc memcpy from device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device memory region
    void* dev_mem = acc_malloc(1024);

    // Create a host memory region
    void* host_mem = malloc(1024);

    // Initialize the device memory with random data
    for (int i = 0; i < 1024; i++) {
        ((char*)dev_mem)[i] = rand() % 256;
    }

    // Copy the device memory to the host memory
    acc_memcpy_from_device(host_mem, dev_mem, 1024);

    // Check that the host memory contains the same data as the device memory
    for (int i = 0; i < 1024; i++) {
        if (((char*)host_mem)[i] != ((char*)dev_mem)[i]) {
            err = 1;
            break;
        }
    }

    // Free the device memory
    acc_free(dev_mem);

    // Free the host memory
    free(host_mem);

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