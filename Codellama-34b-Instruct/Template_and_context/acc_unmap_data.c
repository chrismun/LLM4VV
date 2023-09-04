c
#include "acc_testsuite.h"

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

    // Check that the device data is no longer present
    if (acc_deviceptr(device_data) != NULL) {
        err = 1;
    }

    // Free the host array
    free(host_data);

    return err;
}