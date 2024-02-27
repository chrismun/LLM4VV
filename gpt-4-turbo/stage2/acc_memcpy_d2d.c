#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:acc_memcpy_d2d, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int arraySize = 1024;
    int *src_array = (int*)malloc(arraySize * sizeof(int));
    int *dest_array = (int*)malloc(arraySize * sizeof(int));
    int *verification_array = (int*)malloc(arraySize * sizeof(int));
    
    // Initialize src_array with random data
    for(int i = 0; i < arraySize; ++i){
        src_array[i] = rand();
    }

    // Assuming at least two devices for the sake of demonstration
    int device_count = acc_get_num_devices(acc_device_not_host);
    if (device_count < 2){
        printf("Requires at least two non-host devices for this test.\n");
        free(src_array);
        free(dest_array);
        free(verification_array);
        return -1; // Test cannot proceed
    }

    // Select the first device and copy data from host to device
    acc_set_device_num(0, acc_device_not_host);
    int *device_src_array = (int*)acc_copyin(src_array, arraySize * sizeof(int));

    // Select the second device for destination
    acc_set_device_num(1, acc_device_not_host);
    int *device_dest_array = (int*)acc_malloc(arraySize * sizeof(int));
    
    // Perform device to device copy
    acc_memcpy_d2d(device_dest_array, device_src_array, arraySize * sizeof(int), 1, 0);

    // Copy data from device back to host for verification
    acc_memcpy_from_device(verification_array, device_dest_array, arraySize * sizeof(int));
    
    // Verify the data was copied correctly
    for (int i = 0; i < arraySize; ++i) {
        if (src_array[i] != verification_array[i]) {
            err = 1; // Data mismatch
            break;
        }
    }

    free(src_array);
    free(dest_array);
    free(verification_array);
    acc_free(device_src_array);
    acc_free(device_dest_array);

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