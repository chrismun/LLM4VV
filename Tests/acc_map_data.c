#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create an array of integers on the host
    int* host_array = (int*)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++) {
        host_array[i] = i;
    }

    // Create an array of integers on the device
    int* device_array = (int*)malloc(sizeof(int) * N);

    // Map the host array to the device array
    #pragma acc map(host_array[0:N])

    // Copy the host array to the device array
    #pragma acc update device(host_array[0:N])

    // Verify that the device array contains the same values as the host array
    for (int i = 0; i < N; i++) {
        if (device_array[i] != host_array[i]) {
            err = 1;
            break;
        }
    }

    // Free the host and device arrays
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