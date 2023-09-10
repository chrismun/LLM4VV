#include "acc_testsuite.h"
#ifndef T1
//T1:async clause,V:2.7-3.3
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
    int build_failed;
    int host_failed;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
        build_failed = 0;
        host_failed = 0;
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}