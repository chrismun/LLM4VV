#include "acc_testsuite.h"
#ifndef T1
//T1:atomic construct,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t prev_setting = powf(2, expnt);
    #pragma acc data copyin(a[0:10])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < 10; ++x){
                #pragma acc atomic update
                    a[10] = powf(a[x], expnt);
            }
        }
    }

    realtime_t maxdiff = 0;
    for (int x = 0; x < 10; ++x){
        if (fabs(a[x] - (a[x]/prev_setting)) > maxdiff){
            maxdiff = fabs(a[x] - (a[x]/prev_setting));
        }
        prev_setting = a[x];
    }

    if (maxdiff > PRECISION){
        err += 1;
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