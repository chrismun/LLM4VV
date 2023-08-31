#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create an array of 1000 integers
    int a[1000];

    // Initialize the array with random values
    for (int i = 0; i < 1000; i++){
        a[i] = rand();
    }

    // Create an asynchronous data transfer operation
    acc_async_data_transfer(a, a, 1000);

    // Wait for the asynchronous data transfer operation to complete
    acc_wait(a, a, 1000);

    // Check if the array has been modified
    for (int i = 0; i < 1000; i++){
        if (a[i] != i){
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