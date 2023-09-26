#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:loop construct seq clause,V:2.7-3.3
int test1(){
    int err = 0;
    int arraySize = 100;
    float *array = (float *)malloc(arraySize * sizeof(float));
    srand(SEED);
    
    float accSum = 0.0f;
    float normalSum = 0.0f;
    
    // Initialize the array with random values
    for(int i = 0; i < arraySize; i++){
        array[i] = rand()/(float)RAND_MAX;
        normalSum += array[i];
    }
    
    // Compute the sum using OpenACC loop construct seq clause
    #pragma acc parallel copyin(array[0:arraySize]) reduction(+:accSum)
    {
        #pragma acc loop seq
        for(int i = 0; i < arraySize; i++){
            accSum += array[i];
        }
    }
    
    // Check if the sum from OpenACC matches the normal sum
    if(abs(accSum - normalSum) > 0.001){
        err = 1;
    }

    free(array);
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