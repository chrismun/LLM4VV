#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create an array of 100 integers
    int a[100];

    // Initialize the array with random values
    for (int i = 0; i < 100; i++){
        a[i] = rand();
    }

    // Create a new array of 100 integers
    int b[100];

    // Copy the values from the first array to the second array
    #pragma acc parallel async(a, b)
    for (int i = 0; i < 100; i++){
        b[i] = a[i];
    }

    // Check if the values in the second array are the same as the values in the first array
    for (int i = 0; i < 100; i++){
        if (b[i] != a[i]){
            err = 1;
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