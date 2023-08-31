#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize the input and output arrays
    int input[N];
    int output[N];
    for (int i = 0; i < N; i++){
        input[i] = rand();
        output[i] = 0;
    }

    // Copy the input array to the output array using the copy clause
    #pragma acc parallel loop copy(input[0:N])
    for (int i = 0; i < N; i++){
        output[i] = input[i];
    }

    // Check if the output array is equal to the input array
    for (int i = 0; i < N; i++){
        if (output[i] != input[i]){
            err = 1;
            break;
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