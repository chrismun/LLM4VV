#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct reduction clause,V:2.7-3.3
int test1(){
    int err = 0;
    int x = 0;
    const int I = 100;

    #pragma acc parallel copy(x)
    {
        #pragma acc loop reduction(+:x)
        for (int i = 0; i < I; ++i) {
            x += 1;
        }
    }

    if (x != I) {
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
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}