#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/*T1:data construct copy clause,V:2.0-2.7*/
int test1(){
    int err = 0; // Initial error value
    srand(SEED); // Seed the random number based on SEED value
    
    int array_length = 1000; 
    float* h_array = (float*)malloc(array_length * sizeof(float));
    
    // Random initialization of array
    for (int i = 0; i < array_length; ++i) {
        h_array[i] = rand();
    }

    // OpenACC data construct with copy clause
#pragma acc data copy(h_array[0:array_length])
    {
#pragma acc parallel loop // OpenACC parallel loop
        for (int i = 0; i < array_length; ++i) {
            h_array[i] = h_array[i] + 1.0f;
        }
    }
    // Verification of OpenACC operations
    for (int i = 0; i < array_length; ++i) {
        if (h_array[i] != 1.0f + i) {
            err = 1; // Error code if OpenACC operations not performed as expected
        }
    }
    free(h_array);
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