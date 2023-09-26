#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/*T1:shutdown directive,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc data copy(err)
    {
        #pragma acc parallel num_gangs(1) copy(err)
        {
            err = 1;
        }

        #pragma acc shutdown

        #pragma acc parallel num_gangs(1) copy(err)
        {
            err = 2;
        }
    }

    if(err != 2){
        err = 1;
    }else{
        err = 0;
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