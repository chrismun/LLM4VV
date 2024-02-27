#include "acc_testsuite.h"
#ifndef T1
//T1:cache directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc cache(rand[0:10])
    #pragma acc data copy(err)
    {
        #pragma acc parallel loop reduction(+:err)
        for (int x = 0; x < n; ++x){
            err += rand[10];
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