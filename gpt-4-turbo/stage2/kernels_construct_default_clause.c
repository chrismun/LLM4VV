#include "acc_testsuite.h"
#ifndef T1
//T1:kernels construct default clause, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Given data for the test
    const int data_size = 100;
    int original_array[data_size];
    int result_array[data_size];
    
    // Initialize original array with random data
    for (int i = 0; i < data_size; ++i){
        original_array[i] = rand() % 100;
    }

    // Use OpenACC kernels construct with default clause
    #pragma acc kernels default(present)
    {
        #pragma acc loop
        for (int i = 0; i < data_size; ++i){
            result_array[i] = original_array[i] * 2;
        }
    }

    // Verify the results
    for (int i = 0; i < data_size; ++i){
        if(result_array[i] != original_array[i] * 2){
            err += 1; // Increment error count if mismatch is found
        }
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
#ifndef T1
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}