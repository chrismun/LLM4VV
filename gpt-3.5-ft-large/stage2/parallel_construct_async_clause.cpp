#include "acc_testsuite.h"
#ifndef T1
//T1:parallel construct async clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if(){
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
    int async_result;
    int t1 = 600, t2 = 1200;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
    
        async_result = 0;
        #pragma acc parallel 
        async_result = 1;

        if(async_result != 0){
            failed++;
        }
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}