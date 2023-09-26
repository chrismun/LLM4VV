#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
//T1:acc create,V:2.7-3.3
int test1(){
    int err = 0;
    float* hostArray;
    float* deviceArray;
    int length = 100000;
    srand(SEED);

    hostArray = (float*)malloc(length*sizeof(float));

    for(int i=0 ; i<length ; ++i){
        hostArray[i] = (float)i;
    }

    #pragma acc enter data create(deviceArray[:length])

    if (acc_is_present(deviceArray, length*sizeof(float)) == 0){
        err = 1;
    }

    #pragma acc exit data delete(deviceArray[:length])
  
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