#include <stdlib.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:{acc_deviceptr},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int arraySize = 1024;
    int* hostArray = (int*)malloc(sizeof(int) * arraySize);
    int* deviceArray;
    int* devicePtr;

    // Initialize host array
    for(int i = 0; i < arraySize; ++i){
        hostArray[i] = rand() / (RAND_MAX / 100); // Initialize with random values 0-99
    }

    #pragma acc enter data copyin(hostArray[0:arraySize])
    deviceArray = acc_deviceptr(hostArray);

    // Verify acc_deviceptr works by adding a constant in a parallel region using the device pointer
    int addValue = 5;
    #pragma acc parallel deviceptr(deviceArray)
    {
        for(int i = 0; i < arraySize; i++){
            deviceArray[i] += addValue;
        }
    }

    // Copy back to host to verify
    #pragma acc exit data copyout(hostArray[0:arraySize])

    // Verification
    for(int i = 0; i < arraySize; ++i){
        if(hostArray[i] != (deviceArray[i] - addValue)){
            err++;
            break; // One error is enough to fail the test
        }
    }

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
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}