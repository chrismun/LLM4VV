#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a host data region with a random number of elements
    int num_elements = rand() % 100;
    int* host_data = (int*)malloc(num_elements * sizeof(int));

    // Initialize the host data region with random values
    for (int i = 0; i < num_elements; i++) {
        host_data[i] = rand();
    }

    // Create a device data region with the same number of elements as the host data region
    int* device_data = (int*)malloc(num_elements * sizeof(int));

    // Copy the host data region to the device data region
    acc_memcpy_to_device(device_data, host_data, num_elements * sizeof(int));

    // Create a host_data construct with the if_present clause
    acc_host_data_construct(device_data, num_elements, if_present);

    // Check if the device data region is present
    if (acc_device_data_present(device_data, num_elements)) {
        // If the device data region is present, copy the data back to the host
        acc_memcpy_from_device(host_data, device_data, num_elements * sizeof(int));
    } else {
        // If the device data region is not present, set the error flag
        err = 1;
    }

    // Free the device data region
    acc_free(device_data);

    // Free the host data region
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