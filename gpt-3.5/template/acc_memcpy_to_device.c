#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;

    // Declare variables
    int N = 100;
    int *hostArray, *deviceArray;

    // Allocate memory on host
    hostArray = (int*)malloc(N * sizeof(int));
    if (hostArray == NULL){
        return 1;
    }

    // Initialize host array
    for (int i = 0; i < N; i++){
        hostArray[i] = i + 1;
    }

    // Allocate memory on device
    #pragma acc data create(deviceArray[0:N])
    {
        // Transfer data from host to device
        #pragma acc host_data use_device(deviceArray)
        #pragma acc update device(deviceArray[0:N])

        // Verify the data transfer
        #pragma acc parallel loop
        for (int i = 0; i < N; i++){
            if (deviceArray[i] != (i + 1)){
                err = 1;
                break;
            }
        }
    }

    // Free memory on host
    free(hostArray);

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
        failcode += (1 << 0);
    }
#endif

    return failcode;
}