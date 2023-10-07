#include "acc_testsuite.h"
#ifndef T1
//T1:declare directive link clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    float a = rand() / (float) RAND_MAX;
    float b = 0.0;

    #pragma acc declare link(a)

    #pragma acc parallel copy(b)
    {
        b = a;
    }

    if(fabs(b - a) > PRECISION){
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