#include "acc_testsuite.h"
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
/*T1:loop construct gang clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int num_gangs = 128;
    int num_vectors = 32;
    int size = num_gangs * num_vectors;
    float *result_arr = (float*)malloc(sizeof(float) * size);
    float actual_result = 0.0, computed_result = 0.0;

    for(int i=0; i<size; i++)
        result_arr[i] = i;

    // Perform a parallelized sum
    #pragma acc parallel loop gang 
    for(int i=0; i<size; i++){
        #pragma acc loop vector
        for(int j=i; j<size; j++){
            result_arr[i] += j;
        }
    }

    // Calculate the total sum
    for(int i=0; i<size; i++)
        computed_result += result_arr[i];

    // Calculate actual result
    for(int i=0; i<size; i++)
        for(int j=i; j<size; j++)
            actual_result += j;

    // Check if the computation was properly parallelized
    if(computed_result != actual_result){
        err = 1;
    }

    free(result_arr);
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
        failcode = failcode + (1 << 0); //bitwise shift to notify first test failed
    }
#endif
    return failcode;
}