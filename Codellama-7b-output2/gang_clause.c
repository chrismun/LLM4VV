#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create an array of 1000 integers
    int a[1000];
    for (int i = 0; i < 1000; i++){
        a[i] = rand();
    }

    // Use the gang clause to parallelize the loop
    #pragma acc parallel loop gang
    for (int i = 0; i < 1000; i++){
        a[i] = a[i] * 2;
    }

    // Check that the array is correctly parallelized
    for (int i = 0; i < 1000; i++){
        if (a[i] != 2 * a[i]){
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