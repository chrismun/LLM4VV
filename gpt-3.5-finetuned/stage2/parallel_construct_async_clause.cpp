#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,async,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = new real_t[1024];
    real_t *b = new real_t[1024];

    for (int x = 0; x < 1024; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc data copyin(a[0:1024]) copyout(b[0:1024])
    {
        #pragma acc parallel async(1)
        {
            #pragma acc loop
            for (int x = 0; x < 1024; ++x){
                b[x] = a[x];
            }
        }
    }
    #pragma acc update host(b[0:1024]) async(1)
    #pragma acc wait
    for (int x = 0; x < 1024; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
            err += 1;
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