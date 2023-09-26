#include "acc_testsuite.h"

#ifndef T1
//T1:acc unmap data,V:2.7-3.3
int test1(){
    int err = 0;

    // Allocate some host memory
    int *host_data = (int*)malloc(sizeof(int));
    *host_data = 1234;

    // Map the host memory to the device
    int *device_data = (int*)acc_map_data(host_data, sizeof(int));

    // Unmap the device memory from the host
    acc_unmap_data(device_data);

    // Check that the device memory is no longer mapped to the host
    if (acc_is_mapped(device_data) != 0) {
        err = 1;
    }

    // Free the host memory
    free(host_data);

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