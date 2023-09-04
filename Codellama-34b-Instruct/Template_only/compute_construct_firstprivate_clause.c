#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int a = 1;
    int b = 2;
    int c = 3;

    #pragma acc parallel
    {
        #pragma acc loop
        for (int i = 0; i < 10; ++i) {
            a = a + b;
            b = b + c;
            c = c + a;
        }
    }

    if (a != 11 || b != 12 || c != 13) {
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