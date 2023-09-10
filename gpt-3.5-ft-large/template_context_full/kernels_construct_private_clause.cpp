#include "acc_testsuite.h"
#ifndef T1
//T1:kernels construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if(){
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
    bool test_run = false;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
        if(summary_1 == 0){
            test_run = true;
        }
    }
#endif
    return failcode;
}