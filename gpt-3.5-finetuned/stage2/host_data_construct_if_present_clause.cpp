#include "acc_testsuite.h"
#ifndef T1
//T1:host_data construct if_present clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    for (k = 0; k < loops; k++) {
        for (int x = 0; x < M; ++x){
            a_new[x] = 0.0;
        }
    }

    #pragma acc data copyin(a[0:M]) present(a[0:M:M])
    {
        #pragma acc host_data use_device(a)
        {
            for (k = 0; k < loops; k++) {
                #pragma acc parallel loop async
                for (int x = 0; x < M; ++x) {
                    a[x] += 1;
                }
                #pragma acc wait
            }
        }
    }

    for (int x = 0; x < M; ++x) {
        if (fabs(a_new[x] - a[x]) > PRECISION) {
            err += 1;
        }
    }

    return err;
}

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