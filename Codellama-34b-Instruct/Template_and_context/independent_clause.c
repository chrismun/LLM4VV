c
#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a random array of integers
    int* arr = (int*)malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; i++) {
        arr[i] = rand() % 100;
    }

    // Create a parallel region with the independent clause
    #pragma acc parallel independent
    {
        // Create a local variable to store the sum of the array elements
        int sum = 0;

        // Loop over the array and calculate the sum of the elements
        for (int i = 0; i < 10; i++) {
            sum += arr[i];
        }

        // Check if the sum is equal to the expected value
        if (sum != 100) {
            err = 1;
        }
    }

    free(arr);

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