#include "acc_testsuite.h"
#ifndef T1
/*T1:routine directive,V:2.0-2.7*/
#pragma acc routine seq
int test1(){
    int err = 0;
    srand(SEED);

    for (int x = 0; x < 100; ++x){
        int a = rand() % 100;
        int b = rand() % 100;
        if (a + b != b + a){
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