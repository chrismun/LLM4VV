#include "acc_testsuite.h"

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a 2D array of size 10x10
    int arr[10][10];

    // Initialize the array with random values
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            arr[i][j] = rand();
        }
    }

    // Create a loop construct with a collapse clause
    #pragma acc parallel loop collapse(2)
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            // Do something with the array elements
            arr[i][j] += 1;
        }
    }

    // Check if the collapse clause was applied correctly
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (arr[i][j] != arr[i][j] + 1) {
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