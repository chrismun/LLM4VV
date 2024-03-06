#include "acc_testsuite.h"

#ifndef T1
//T1:data construct no_create clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int host_var = 10;

    #pragma acc data copyin(host_var)
    {
        #pragma acc parallel no_create(host_var)
        {
            // do something with host_var
            host_var = 20;
        }
    }

    if (host_var != 20) {
        err++;
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