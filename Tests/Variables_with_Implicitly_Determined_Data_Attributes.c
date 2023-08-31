#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create an array of integers with a size that is a power of 2
    int array[1 << 10];

    // Initialize the array with random values
    for (int i = 0; i < 1 << 10; i++){
        array[i] = rand();
    }

    // Use the array in a parallel region
    #pragma acc parallel loop
    for (int i = 0; i < 1 << 10; i++){
        array[i] = array[i] * array[i];
    }

    // Check that the array has the correct values
    for (int i = 0; i < 1 << 10; i++){
        if (array[i] != (array[i] * array[i])){
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