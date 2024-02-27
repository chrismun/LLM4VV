#include "acc_testsuite.h"
#ifndef T1
// T1:memcpy_device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 128;
    int *host_array = (int*)malloc(size * sizeof(int));
    int *device_array;

    // Initializing host data
    for(int i = 0; i < size; ++i){
        host_array[i] = i;
    }

    // Allocating device memory
    device_array = (int*)acc_malloc(size * sizeof(int));

    // Copying data to the device
    acc_memcpy_to_device(device_array, host_array, size * sizeof(int));

    // Modifying data on the device
    #pragma acc parallel loop copyin(device_array[0:size])
    for(int i = 0; i < size; ++i){
        device_array[i] += 10;
    }

    // Copying data back to host to verify
    acc_memcpy_from_device(host_array, device_array, size * sizeof(int));

    // Verifying the computation
    for(int i = 0; i < size; ++i){
        if(host_array[i] != i + 10){
            err++;
        }
    }

    // Cleanup
    free(host_array);
    acc_free(device_array);
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