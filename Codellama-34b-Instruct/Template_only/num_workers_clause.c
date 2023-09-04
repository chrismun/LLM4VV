#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int num_workers = 4; // Set the number of workers to 4
    int num_threads = 8; // Set the number of threads to 8

    // Create an array of integers to be processed in parallel
    int arr[100];
    for (int i = 0; i < 100; i++) {
        arr[i] = i;
    }

    // Create a parallel region with the specified number of workers
    #pragma acc parallel num_workers(num_workers)
    {
        // Create a loop to process the array in parallel
        #pragma acc loop
        for (int i = 0; i < 100; i++) {
            arr[i] = arr[i] * 2;
        }
    }

    // Check the results of the parallel loop
    for (int i = 0; i < 100; i++) {
        if (arr[i] != i * 2) {
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