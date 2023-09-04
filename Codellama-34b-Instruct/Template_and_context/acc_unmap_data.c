#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a host array
    int *host_data = (int *)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        host_data[i] = i;
    }

    // Map the host array to the device
    int *device_data = (int *)acc_map_data(host_data, sizeof(int) * 10);

    // Unmap the device data
    acc_unmap_data(device_data);

    // Check that the device data is no longer mapped
    if (acc_is_present(device_data, sizeof(int) * 10) != 0) {
        err = 1;
    }

    // Free the host array
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