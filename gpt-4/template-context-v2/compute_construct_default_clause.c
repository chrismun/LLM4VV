#include "acc_testsuite.h"

#ifndef T1
//T1:compute construct default clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    int a = rand() % 100; // any random number
    int b = 0;

#pragma acc parallel copyin(a) copy(b)
{
#pragma acc loop seq
    for (int i = 0; i < 1; i++) {
        #pragma acc compute_construct default(none)
        {
            b = a;
        }
    }
}

    //If the value of b is not equal to a then mark an error
    if(b != a){
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