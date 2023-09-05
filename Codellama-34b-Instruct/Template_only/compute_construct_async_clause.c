#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a random number between 1 and 100
    int num = rand() % 100 + 1;

    // Create an array of size num
    int* arr = (int*)malloc(num * sizeof(int));

    // Initialize the array with random values
    for (int i = 0; i < num; i++) {
        arr[i] = rand() % 100;
    }

    // Create a parallel region with the async clause
    #pragma acc parallel async(arr)
    {
        // Perform some computation on the array
        for (int i = 0; i < num; i++) {
            arr[i] = arr[i] + 1;
        }
    }

    // Check that the array has been updated correctly
    for (int i = 0; i < num; i++) {
        if (arr[i] != arr[i] + 1) {
            err = 1;
            break;
        }
    }

    // Free the array
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