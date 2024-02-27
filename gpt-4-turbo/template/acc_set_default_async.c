#include "acc_testsuite.h"
#ifndef T1
//T1:async,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int* host_array = (int*)malloc(size * sizeof(int));
    int* device_array = (int*)malloc(size * sizeof(int));

    // Initialize the arrays
    for (int i = 0; i < size; ++i){
        host_array[i] = rand() / (RAND_MAX / 100);
    }

    // Set the default async behavior
    acc_set_default_async(1);

    // Copy data to the device asynchronously
    #pragma acc enter data copyin(host_array[0:size]) async(1)

    // Perform some computation on the device asynchronously
    #pragma acc parallel loop async(1)
    for (int i = 0; i < size; ++i){
        host_array[i] = host_array[i] * 2;
    }

    // Copy data back from the device asynchronously
    #pragma acc exit data copyout(device_array[0:size]) async(1)

    // Wait for all async operations to complete
    acc_wait(1);

    // Verify the results
    for (int i = 0; i < size; ++i) {
        if (device_array[i] != host_array[i]) {
            err += 1;
        }
    }

    free(host_array);
    free(device_array);

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