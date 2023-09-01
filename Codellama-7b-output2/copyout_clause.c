#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize the input and output arrays
    int *input = (int *)malloc(N * sizeof(int));
    int *output = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        input[i] = i;
        output[i] = 0;
    }

    // Copy the input array to the output array using the copyout clause
    #pragma acc parallel copyout(output[0:N])
    {
        for (int i = 0; i < N; i++) {
            output[i] = input[i];
        }
    }

    // Check if the output array is equal to the input array
    for (int i = 0; i < N; i++) {
        if (output[i] != input[i]) {
            err = 1;
            break;
        }
    }

    // Free the memory allocated for the input and output arrays
    free(input);
    free(output);

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