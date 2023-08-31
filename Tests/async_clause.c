#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create an array of integers
    int *data = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        data[i] = rand() % 100;
    }

    // Create a kernel that computes the sum of the array elements
    int *result = (int *)malloc(sizeof(int));
    *result = 0;
    #pragma acc parallel async(data)
    {
        #pragma acc loop
        for (int i = 0; i < N; i++) {
            *result += data[i];
        }
    }

    // Wait for the kernel to complete
    #pragma acc wait(data)

    // Check if the result is correct
    if (*result != (N * (N - 1)) / 2) {
        err = 1;
    }

    // Free the memory
    free(data);
    free(result);

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