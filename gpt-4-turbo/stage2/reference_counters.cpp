#include <iostream>
#include <openacc.h>
#include <stdlib.h>

#ifndef T1
// T1:reference counters,V:2.7-3.3
int test1() {
    int err = 0;
    const int size = 1024;
    int* host_array = (int*)malloc(size * sizeof(int));
  
    // Initialize array
    for (int i = 0; i < size; ++i) {
        host_array[i] = i;
    }

    // Explicitly manage device memory using OpenACC API
    acc_init(acc_device_default);

    // Copy data to the device to increase dynamic reference counter
    acc_copyin(host_array, size * sizeof(int));

    // Enter data region to increase structured reference counter
    #pragma acc data copy(host_array[0:size])
    {
        // Perform some dummy operations
        #pragma acc parallel loop
        for (int i = 0; i < size; ++i) {
            host_array[i] += 1;
        }
    } // Exiting data region, decrease structured reference counter

    // Decrease dynamic reference counter, should not deallocate yet as structured is still > 0
    acc_delete(host_array, size * sizeof(int));

    // Check if data is still present on device
    if (!acc_is_present(host_array, size * sizeof(int))) {
        err += 1; // Data should not have been deallocated yet
    }

    // This should deallocate the data from the device
    #pragma acc exit data delete(host_array[0:size])

    if (acc_is_present(host_array, size * sizeof(int))) {
        err += 1; // Data should have been deallocated
    }

    free(host_array);
    acc_shutdown(acc_device_default);
  
    return err;
}
#endif

int main() {
    int failcode = 0;
    const int NUM_TEST_CALLS = 1; // Adjust based on desired repetitions

    int failed = test1();
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}