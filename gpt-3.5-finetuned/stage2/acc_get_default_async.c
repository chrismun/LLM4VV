#include "acc_testsuite.h"

int test1(){
    int err = 0;
    int a = 30;

    #pragma acc parallel async(acc_get_default_async())
    {
        #pragma acc loop
        for (int x = 0; x < a; ++x){
            ;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}