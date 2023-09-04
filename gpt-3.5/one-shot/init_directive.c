#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,data,data-region,V:1.0-2.6
int test1(){
    int err = 0;
    int b = 1;

    #pragma acc parallel init(b)
    {
        b = 0;
    }

    if (b != 1){
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