#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct reduction clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int sum = 0;
    int x;
    
    #pragma acc parallel loop reduction(+:sum)
    for (x = 0; x < 100; ++x){
        sum += x;
    }

    int expected_sum = 0;
    for (x = 0; x < 100; ++x){
        expected_sum += x;
    }

    if (sum != expected_sum){
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