#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create an array of 1000 elements
    int arr[1000];

    // Initialize the array with random values
    for (int i = 0; i < 1000; i++){
        arr[i] = rand();
    }

    // Use the seq clause to specify that the array should be accessed in sequential order
    #pragma acc seq(arr)
    {
        // Access the array in sequential order
        for (int i = 0; i < 1000; i++){
            if (arr[i] != i){
                err = 1;
                break;
            }
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