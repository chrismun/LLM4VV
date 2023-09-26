#include "acc_testsuite.h"
#ifndef T1
//T1:parallel construct wait clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    acc_init(acc_device_altera);

    #pragma acc parallel async(1)
    {
        #pragma acc loop
        for (int i = 0; i < 10; ++i){
            dev_out = i;
        }
    }
    #pragma acc parallel wait(async:1)
    {
        #pragma acc loop
        for (int i = 0; i < 10; ++i){
            if (dev_out > 9){
                err += 1;
            }
        }
    }

    acc_shutdown(acc_device_altera);

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