#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>
#include "acc_testsuite.h"

int test_data_present() {
    int err = 0;
    int *hostArray;
    int * deviceArray;

    int arraySize = 1024;
    hostArray = (int*) malloc(arraySize * sizeof(int)); 

    for (int i = 0; i < arraySize; ++i){
        hostArray[i] = rand();
    }

    #pragma acc enter data copyin(hostArray[0:arraySize])
    deviceArray = acc_deviceptr(hostArray);

    #pragma acc parallel present(hostArray[0:arraySize])
    for (int i = 0; i < arraySize; ++i) {
        if(hostArray[i] != deviceArray[i]) {
            err = 1;
        }
    }
    #pragma acc exit data delete(hostArray[0:arraySize])

    free(hostArray);
    return err;
}

int main() {
    int failCode = 0;
    int failed;
    failed = 0;
    
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_data_present();
    }
    
    if (failed != 0){
        failCode = failCode + (1 << 0);
    }

    return failCode;
}