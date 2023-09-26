#include "acc_testsuite.h"
#ifndef T1
//T1:declare directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    //#pragma acc declare create(a)
    int a[10];

    for (int x = 0; x < 10; ++x){
        a[x] = 0;
    }

    #pragma acc parallel
    {
        #pragma acc loop
        for (int x = 0; x < 10; ++x){
            a[x] = 1;
        }
    }

    for (int x = 0; x < 10; ++x){
        if (a[x] != 1){
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