#include "acc_testsuite.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef T1
/*T1:acc_memcpy_from_device,V:2.0-2.7*/
int test1(){
    int err = 0;
    float *hostData;
    float *devData;
    const int dataSize = 1024;

    srand(SEED);

    // Allocate host and device buffer
    hostData = new float[dataSize]();
    devData = static_cast<float*>(acc_malloc(dataSize*sizeof(float)));

    // Fill device buffer with some values
    #pragma acc parallel loop present(devData[0:dataSize])
    for (int i=0; i < dataSize; i++) {
        devData[i] = rand();
    }

    // Copy from device to host buffer
    acc_memcpy_from_device(hostData, devData, dataSize*sizeof(float));

    // Verify the results
    #pragma acc parallel loop present(devData[0:dataSize])
    for (int i = 0; i < dataSize; ++i){
        if(hostData[i] != devData[i]){
            err = 1;
            break;
        }
    }

    // Cleanup
    acc_free(devData);
    delete[] hostData;

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