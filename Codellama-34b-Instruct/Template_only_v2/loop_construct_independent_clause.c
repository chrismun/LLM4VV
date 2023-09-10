#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct independent clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc parallel loop independent
    for (int i = 0; i < 10; i++) {
        #pragma acc loop independent
        for (int j = 0; j < 10; j++) {
            #pragma acc loop independent
            for (int k = 0; k < 10; k++) {
                // Do some computation here
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