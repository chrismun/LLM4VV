#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct reduction clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int x = 0;

    #pragma acc parallel copy(x) reduction(+:x)
    {
        #pragma acc loop gang worker vector reduction(+:x)
        for (int i = 0; i < 10; i++){
            x += i;
        }
    }

    for (int i = 0; i < 10; i++){
        x -= i;
    }

    if (x != 0){
        err += 1;
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