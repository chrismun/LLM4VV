#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create an array with a large number of elements
    int array[1000];
    for (int i = 0; i < 1000; i++){
        array[i] = rand() % 100;
    }

    // Use the collapse clause to collapse the array into a single value
    int result = 0;
    #pragma acc parallel loop collapse(1)
    for (int i = 0; i < 1000; i++){
        result += array[i];
    }

    // Check that the result is correct
    if (result != 49500){
        err = 1;
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