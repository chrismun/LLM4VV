#include "acc_testsuite.h"
#ifndef T1
//T1:loop,auto,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int total = 0;

    #pragma acc parallel loop auto reduction(+:total)
    for (int m = 0; m < 20; ++m){
        int toggle = 0;
        int new = 1;
        for (int n = 0; n < 20; ++n){
            if (toggle == 0){
                new = 5;
                toggle = 1;
            }
            total += new;
        }
    }
    total = 20 * 20 * 5;
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