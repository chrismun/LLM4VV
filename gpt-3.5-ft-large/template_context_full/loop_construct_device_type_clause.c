#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct device_type clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc data copy(from: *(x - n)) copy(to: *(x + n))
    {
        #pragma acc parallel
        {
            #pragma acc loop device_type(fpga) independent
            for (int x = 0; x < n; ++x){
                x[x + n] = x;
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if ((x[n] < x - PRECISION) && (x[n] > x + PRECISION)){
            err = 1;
        }
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