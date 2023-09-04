#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize data
    int data[10];
    for (int i = 0; i < 10; i++) {
        data[i] = rand() % 100;
    }

    // Create a parallel region with a combined construct
    #pragma acc parallel loop
    for (int i = 0; i < 10; i++) {
        #pragma acc loop
        for (int j = 0; j < 10; j++) {
            data[i] += data[j];
        }
    }

    // Check the results
    for (int i = 0; i < 10; i++) {
        if (data[i] != 100) {
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