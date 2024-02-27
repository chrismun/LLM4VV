#include "acc_testsuite.h"
#ifndef T1
//T1:wait directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc data copyin(repeat[0:1]) copy(x[0:1])
    {
        for (int k = 0; k < 5; ++k){
            for (int y = 0; y < 2; ++y){
                delays[k*2 + y] = k;
                #pragma acc parallel async(k*2 + y)
                {
                    int t = 10;
                    for (int n = 0; n < 1000; ++n){
                        t = (int) exp(log(fabs(repeat[y] + x[y]))) % 2;
                    }
                    x[y] += t;
                }
            }
            #pragma acc update device(x[:2]) async(k*2)
            #pragma acc wait
            #pragma acc update device(x[:2]) async(k*2 + 1)
            #pragma acc wait
        }
    }
    for (int k = 0; k < 5; ++k){
        for (int y = 0; y < 2; ++y){
            if (x[y] != 10){
                err += 1;
            }
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