#include "acc_testsuite.h"

#ifndef T1
/*T1:loop construct device_type clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int hostArr[SIZE], deviceArr[SIZE];

    // Initialize host array
    for(int i = 0; i < SIZE; ++i){
        hostArr[i] = rand();
    }

    #pragma acc data copy(deviceArr)
    {
        #pragma acc parallel loop device_type(nvidia,host) copy(hostArr)
        for(int i = 0; i < SIZE; ++i){
            deviceArr[i] = hostArr[i];
        }
    }

   // Validation
   for(int i = 0; i < SIZE; ++i){
        if(hostArr[i] != deviceArr[i]){
            err = 1;
        }
    }

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