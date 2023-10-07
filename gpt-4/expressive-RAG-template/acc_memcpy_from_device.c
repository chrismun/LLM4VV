#include "acc_testsuite.h"
#include <stdlib.h>
#include <string.h>

#ifndef T1
//T1:acc memcpy from device,V:2.7-3.3

int test1(){
    int err = 0;
    srand(SEED);

    int size = 100; //size of array to be transferred
    int* host_array = (int*) malloc(size * sizeof(int));
    int* device_array;
    size_t data_size = size * sizeof(int); 

    //initialize host array
    for (int i = 0; i < size; i++) {
        host_array[i] = rand() % 100;
    }

    // Allocate memory on the device
    #pragma acc data create(device_array[size])
    {
        // Copy data to the device
        #pragma acc update device(device_array[:size])
        memcpy(device_array, host_array, data_size);

        // Copy the data back to the host array
        acc_memcpy_from_device(host_array, device_array, data_size);

        // Verify the copied data
        for (int i = 0; i < size; i++) {
            if (host_array[i] != device_array[i]) {
                err = 1;
                break;
            }
        }
    }

    // clean up
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