#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct seq clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    for (int x = 0; x < n; ++x){
        b[x] = 1.5;
    }

    #pragma acc loop seq
    for (int x = 0; x < n; ++x){
        b[x] = b[x] * 2;
    }

    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - 3) > PRECISION){
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