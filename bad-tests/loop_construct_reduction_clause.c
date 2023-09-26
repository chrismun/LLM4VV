#include "acc_testsuite.h"
#ifndef T1
/*T1: Test OpenAcc Loop construct reduction clause,
   check for a non-private variable "x" reduced by addition,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int I = rand();
    int x = 0;

    #pragma acc parallel copy(x)
    {
        #pragma acc loop gang worker vector reduction(+:x)
        for (int i = 0; i < I; ++i)
            x += 1;
    }

    if(x != I){
        err = 1;
    }
    return err;
}
#endif

#ifndef T2
/*T2: Test OpenAcc Loop construct reduction clause,
   checks for a private variable's (x) reduction by addition,V:2.0-2.7*/
int test2(){
    int err = 0;
    srand(SEED);
    int I = rand();
    int x = 0;

    #pragma acc parallel firstprivate(x)
    {
        #pragma acc loop seq reduction(+:x)
        for (int i = 0; i < I; ++i) {
            x += 1;
        }
    }

    if(x != 0){
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

#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif

    return failcode;
}