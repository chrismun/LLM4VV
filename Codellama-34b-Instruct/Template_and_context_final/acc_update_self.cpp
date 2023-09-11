#include "acc_testsuite.h"

// T1:acc update self,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a device memory region
    int *device_data = (int*)acc_malloc(sizeof(int));
    if (device_data == NULL) {
        err = 1;
    }

    // Create a local memory region
    int *local_data = (int*)malloc(sizeof(int));
    if (local_data == NULL) {
        err = 1;
    }

    // Initialize the local memory region
    *local_data = rand();

    // Update the device memory region from the local memory region
    acc_update_self(device_data, sizeof(int));

    // Check that the device memory region has been updated
    if (*device_data != *local_data) {
        err = 1;
    }

    // Free the device memory region
    acc_free(device_data);

    // Free the local memory region
    free(local_data);

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