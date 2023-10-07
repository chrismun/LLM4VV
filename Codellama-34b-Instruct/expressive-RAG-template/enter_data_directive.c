#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data region with the enter data directive
    #pragma acc enter data copyin(array[0:N])
    {
        // Initialize the array with random values
        for (int i = 0; i < N; i++) {
            array[i] = rand();
        }
    }

    // Check that the array has been copied correctly
    for (int i = 0; i < N; i++) {
        if (array[i] != rand()) {
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