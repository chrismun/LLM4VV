#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <acc_testsuite.h>

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    if(){
        err = 1;
    }

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

void acc_create(h_void *data_arg, size_t bytes){
    // Check if the data is already present in the current device memory
    if (data_arg != NULL && bytes > 0){
        // Allocate space in the current device memory for the data
        d_void *device_data = acc_malloc(bytes);
        if (device_data == NULL){
            // If the allocation fails, return an error
            return 1;
        }
        // Copy the data to the device memory
        memcpy(device_data, data_arg, bytes);
        // Increment the dynamic reference counter
        acc_increment_reference_count(device_data);
        // Return a pointer to the device memory
        return device_data;
    }
    // If the data is not present in the current device memory, return an error
    return 1;
}