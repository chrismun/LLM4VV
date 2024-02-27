#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int a[size];
    int result = 0, host_result = 0;

    // Initialize array with random data and calculate host result for validation
    for(int i = 0; i < size; ++i){
        a[i] = rand() % 100;
        host_result += a[i];
    }

    // Using OpenACC to offload the operation to an accelerator (if available) and perform reduction
    #pragma acc parallel loop reduction(+:result)
    for(int i = 0; i < size; ++i){
        result += a[i];
    }

    // Check if the result computed by OpenACC is equal to the expected host result
    if(result != host_result){
        err += 1; // Error increment if the results do not match
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