#include "acc_testsuite.h"
#ifndef TEST_LOOP_REDUCTION
//TEST_LOOP_REDUCTION:loop construct reduction clause,V:2.7-3.3
int test_loop_reduction(){
    int err = 0;
    int length = 1000;
    int host_array[length];
    int reduction_result = 0;
    
    srand(SEED);
    // Populate the array with random values
    for(int i = 0; i < length; i++){
        host_array[i] = rand() % 1000;
    }

    // Use OpenACC loop directive with reduction clause
    #pragma acc parallel loop reduction (+:reduction_result)
    for(int i = 0;i < length; i++) {
        reduction_result += host_array[i];
    }

    // Check the result with host computation
    int host_result = 0;
    for(int i = 0; i < length; i++){
        host_result += host_array[i];
    }

    if(host_result != reduction_result){
        err = 1;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef TEST_LOOP_REDUCTION
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test_loop_reduction();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}