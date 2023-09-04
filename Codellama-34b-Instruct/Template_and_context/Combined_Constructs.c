c
#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a parallel region with a loop inside
    #pragma acc parallel loop
    for (int i = 0; i < 10; i++) {
        // Create a data region with a loop inside
        #pragma acc data
        for (int j = 0; j < 10; j++) {
            // Create a parallel region with a loop inside
            #pragma acc parallel loop
            for (int k = 0; k < 10; k++) {
                // Create a data region with a loop inside
                #pragma acc data
                for (int l = 0; l < 10; l++) {
                    // Do some computation
                    int result = i * j * k * l;
                    // Check if the result is correct
                    if (result != i * j * k * l) {
                        err = 1;
                        break;
                    }
                }
            }
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