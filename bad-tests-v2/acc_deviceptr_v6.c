#include "acc_testsuite.h"

#ifndef T1
//T1:acc deviceptr,V:2.7-3.3
int test1(){
    int err = 0;

    // Allocate a host array
    int *host_array = (int *)malloc(10 * sizeof(int));

    // Initialize the host array
    for (int i = 0; i < 10; i++) {
        host_array[i] = i;
    }

    // Create a device array
    int *device_array = (int *)acc_malloc(10 * sizeof(int));

    // Copy the host array to the device array
    acc_memcpy(device_array, host_array, 10 * sizeof(int));

    // Get the device pointer for the first element of the device array
    int *device_ptr = (int *)acc_deviceptr(device_array);

    // Check that the device pointer is not null
    if (device_ptr == NULL) {
        err = 1;
    }

    // Check that the device pointer points to the correct location
    if (device_ptr != device_array) {
        err = 1;
    }

    // Free the device array
    acc_free(device_array);

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