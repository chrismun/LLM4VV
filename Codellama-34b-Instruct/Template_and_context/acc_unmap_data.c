#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a host array
    int *host_array = (int*)malloc(sizeof(int) * 10);

    // Map the host array to a device array
    int *device_array = (int*)acc_map_data(host_array, sizeof(int) * 10);

    // Unmap the device array
    acc_unmap_data(device_array);

    // Check that the device array is no longer mapped
    if (acc_is_present(device_array, sizeof(int) * 10) == 0) {
        err = 1;
    }

    // Free the host array
    free(host_array);

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