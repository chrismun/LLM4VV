#include <stdlib.h>
#include <stdio.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int size = 100;
    int *host_data = (int*)malloc(size * sizeof(int));
    int *device_data = (int*)malloc(size * sizeof(int));

    // Initialize host data
    for(int i = 0; i < size; i++) {
        host_data[i] = i;
    }

    // Copy data to device
    #pragma acc data copyin(host_data[:size]) copyout(device_data[:size])
    {
        // Copy data to device and cache it
        #pragma acc kernels
        for(int i = 0; i < size; i++) {
            device_data[i] = host_data[i];
        }
    }

    // Verify data
    for(int i = 0; i < size; i++) {
        if(host_data[i] != device_data[i]) {
            err++;
        }
    }

    free(host_data);
    free(device_data);

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