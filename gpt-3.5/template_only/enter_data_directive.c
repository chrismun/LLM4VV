#include "acc_testsuite.h"

#ifndef T1
// T1: runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Add code to test the enter data directive here
    #pragma acc enter data create(a[0:N])

    // Add code to perform data operations here

    // Add code to test the exit data directive here
    #pragma acc exit data delete(a[0:N])

    // Validate that the data operations were successful
    for (int i = 0; i < N; ++i){
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
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif

    return failcode;
}