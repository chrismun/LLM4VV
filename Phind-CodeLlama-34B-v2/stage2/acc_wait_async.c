#include "acc_testsuite.h"
#ifndef T1
/*T1:acc wait async,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int async = rand() % 2;
    int wait = rand() % 2;

    #pragma acc enter data copyin(wait, async)
    #pragma acc parallel async(async)
    {
        #pragma acc wait(wait) async(async)
    }
    #pragma acc exit data delete(wait, async)

    if (wait != async){
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