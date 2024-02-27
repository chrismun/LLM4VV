#include "acc_testsuite.h"
#ifndef T1
//T1:parallel construct wait clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc parallel
    {
        #pragma acc loop
        for (int n = 0; n < 10000; ++n){
            a[n] = 0.0;
        }
    }
    #pragma acc update device(a[0:1])
    #pragma acc parallel loop
    for (int n = 0; n < 10000; ++n){
        a[n] = 1.0;
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