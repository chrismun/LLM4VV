#include "acc_testsuite.h"

#ifndef T1
//T1:combined constucts,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Test parallelloop construct
    #pragma acc parallel loop
    for (int i = 0; i < 10; i++) {
        // Do some work
    }

    // Test serialloop construct
    #pragma acc serial loop
    for (int i = 0; i < 10; i++) {
        // Do some work
    }

    // Test kernelsloop construct
    #pragma acc kernels loop
    for (int i = 0; i < 10; i++) {
        // Do some work
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