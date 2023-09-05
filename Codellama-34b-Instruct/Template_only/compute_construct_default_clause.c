#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a random number between 1 and 10
    int num = rand() % 10 + 1;

    // Create an array of integers with the same size as the number of threads
    int* arr = (int*)malloc(num * sizeof(int));

    // Initialize the array with random values
    for (int i = 0; i < num; i++) {
        arr[i] = rand() % 100;
    }

    // Create a compute construct with the default clause
    #pragma acc compute default(present)
    {
        // Compute the sum of the array elements
        int sum = 0;
        for (int i = 0; i < num; i++) {
            sum += arr[i];
        }

        // Check if the sum is correct
        if (sum != num * (num + 1) / 2) {
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