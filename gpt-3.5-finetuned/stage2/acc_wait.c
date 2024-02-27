#include "acc_testsuite.h"
#ifndef T1
//T1:acc wait,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc data copy(err)
    {
        #pragma acc parallel loop async(1)
        for(int x = 0; x < n; ++x){
            y[0] = a;
        }
        acc_wait(1);
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