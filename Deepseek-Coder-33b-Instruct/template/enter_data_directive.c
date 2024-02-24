#include <stdlib.h>
#include <stdio.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int N = 100;
    int *host_data = (int*)malloc(N * sizeof(int));
    int *device_data;

    // Initialize host data
    for(int i = 0; i < N; i++) {
        host_data[i] = i;
    }

    // Allocate device memory
    #pragma acc enter data create(device_data[0:N])

    // Copy data from host to device
    #pragma acc update device(device_data[0:N])

    // Check if data was copied correctly
    for(int i = 0; i < N; i++) {
        if(device_data[i] != i) {
            err++;
        }
    }

    // Free device memory
    #pragma acc exit data delete(device_data[0:N])

    // Free host memory
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