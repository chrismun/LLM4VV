#include "acc_testsuite.h"
#ifndef T1
//T1:serial,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = new real_t[1024 * 1024];
    real_t *b = new real_t[1024 * 1024];
    real_t *c = new real_t[1024 * 1024];

    for(int x = 0; x < 1024*1024; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc data copyin(a[0:1024*1024], b[0:1024*1024]) copyout(c[0:1024*1024])
    {
        #pragma acc serial default(present)
        {
            #pragma acc loop 
            for(int x = 0; x < 1024; ++x){
                #pragma acc loop
                for(int y = 0; y < 1024; ++y){
                    c[x * 1024 + y] = a[x * 1024 + y] + b[x * 1024 + y];
                }
            }
        }
    }

    for (int x = 0; x < 1024*1024; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
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