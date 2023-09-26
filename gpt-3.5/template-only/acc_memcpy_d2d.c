#include "acc_testsuite.h"

#ifndef T1
// T1: runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create data arrays
    int* host_data = (int*)malloc(DATA_SIZE * sizeof(int));
    int* device_data1 = (int*)malloc(DATA_SIZE * sizeof(int));
    int* device_data2 = (int*)malloc(DATA_SIZE * sizeof(int));

    // Initialize host_data array
    for (int i = 0; i < DATA_SIZE; ++i){
        host_data[i] = rand();
    }

    // Copy data from host to device using acc_memcpy
    #pragma acc data copy(host_data[0:DATA_SIZE]) \
                     create(device_data1[0:DATA_SIZE]) \
                     copyout(device_data2[0:DATA_SIZE])
    {
        #pragma acc parallel loop
        for (int i = 0; i < DATA_SIZE; ++i){
            device_data1[i] = host_data[i];
        }

        // Copy data from device to device using acc_memcpy
        #pragma acc enter data copyin(device_data1[0:DATA_SIZE])
        #pragma acc parallel loop
        for (int i = 0; i < DATA_SIZE; ++i){
            acc_memcpy(&device_data2[i], &device_data1[i], sizeof(int));
        }
        #pragma acc exit data delete(device_data1[0:DATA_SIZE])
    }

    // Verify data on the device is correct
    for (int i = 0; i < DATA_SIZE; ++i){
        if (host_data[i] != device_data2[i]){
            err = 1;
            break;
        }
    }

    // Free memory
    free(host_data);
    free(device_data1);
    free(device_data2);

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }

    if (failed != 0){
        failcode |= (1 << 0);
    }
#endif

    return failcode;
}