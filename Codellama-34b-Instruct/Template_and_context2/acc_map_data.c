#include "acc_testsuite.h"

#ifndef T1
//T1:acc map data,V:2.7-3.3
int test1(){
    int err = 0;

    // Allocate some memory on the host
    void *host_ptr = malloc(1024);

    // Allocate some memory on the device
    void *device_ptr = acc_malloc(1024);

    // Map the device memory to the host memory
    acc_map_data(host_ptr, device_ptr, 1024);

    // Check that the data is correctly mapped
    if (acc_is_present(host_ptr, 1024) != 1) {
        err = 1;
    }

    // Unmap the device memory
    acc_unmap_data(host_ptr, device_ptr, 1024);

    // Check that the data is no longer mapped
    if (acc_is_present(host_ptr, 1024) != 0) {
        err = 1;
    }

    // Free the device memory
    acc_free(device_ptr);

    // Free the host memory
    free(host_ptr);

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