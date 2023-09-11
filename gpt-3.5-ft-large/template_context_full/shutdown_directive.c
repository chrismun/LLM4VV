#include "acc_testsuite.h"
#ifndef T1
//T1:shutdown directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc shutdown
    for(int x = 0; x < 10; ++x){
        real[x] = rand() / (real)RAND_MAX;
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