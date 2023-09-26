#include "acc_testsuite.h"
#ifndef T1
/*T1:parallel construct if clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc parallel if(1)
    {
        // Do nothing
    }

    #pragma acc parallel if(0)
    {
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