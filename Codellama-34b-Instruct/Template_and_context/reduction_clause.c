#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int a = 0;
    int b = 0;
    int c = 0;

    #pragma acc parallel loop reduction(+:a,b,c)
    for (int i = 0; i < 10; i++) {
        a += i;
        b += i;
        c += i;
    }

    if (a != 45 || b != 45 || c != 45) {
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