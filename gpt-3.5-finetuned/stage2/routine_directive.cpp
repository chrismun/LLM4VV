#include "acc_testsuite.h"
#ifndef T1
//T1:routine,construct-independent,V:1.0-2.7
int addtwo(int a, int b){
    return a + b;
}

int test1(){
    int err = 0;
    srand(SEED);
    #pragma acc routine
    for (int x = 0; x < n; ++x){
        a[x] = addtwo(b[x], c[x]);
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