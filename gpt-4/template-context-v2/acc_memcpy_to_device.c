#include "acc_testsuite.h"
#ifndef T1
//T1:acc memcpy to device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int length = 10000;
    float* hostData = (float*) malloc(length * sizeof(float));
    float* deviceData = (float*) malloc(length * sizeof(float));

    //Filling hostData with random floats
    for (int index = 0; index < length; index++){
        hostData[index] = (float) rand()/(float) (RAND_MAX/20);
    }

    //Copying data to device memory
    acc_memcpy_to_device( deviceData, hostData, length * sizeof(float) );

    //Copying data back to verify
    float* copybackData = (float*) malloc(length * sizeof(float));
    acc_memcpy_from_device( copybackData, deviceData, length * sizeof(float) );
    
    for (int index = 0; index < length; index++){
        if (hostData[index] != copybackData[index]){
            err = 1;
            break;
        }
    }

    free(hostData);
    free(deviceData);
    free(copybackData);

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