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

    // Attach device data
    #pragma acc data copyin(host_data[0:N]) create(device_data[0:N])
    {
        // Copy data from host to device
        #pragma acc update device(device_data[0:N])

        // Verify data on device
        for(int i = 0; i < N; i++) {
            if(device_data[i] != host_data[i]) {
                err++;
            }
        }
    }

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