#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create an array of size 100 and initialize it with random values
    int a[100];
    for (int i = 0; i < 100; i++){
        a[i] = rand();
    }

    // Create a copy of the array and initialize it with zeros
    int b[100];
    for (int i = 0; i < 100; i++){
        b[i] = 0;
    }

    // Use the "copy" directive to copy the contents of a to b
    #pragma acc parallel loop copy(a[0:100])
    for (int i = 0; i < 100; i++){
        b[i] = a[i];
    }

    // Check that the contents of b are the same as the contents of a
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