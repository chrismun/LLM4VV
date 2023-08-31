#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create an array of integers
    int a[10];
    for (int i = 0; i < 10; i++){
        a[i] = rand();
    }

    // Create a copy of the array
    int b[10];
    for (int i = 0; i < 10; i++){
        b[i] = a[i];
    }

    // Exit data directive
    #pragma acc exit data copyin(a[0:10])

    // Check that the copy of the array is the same as the original array
    for (int i = 0; i < 10; i++){
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