#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct worker clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = new real_t[250 * 1024];
    real_t *b = new real_t[250 * 1024];
    real_t *c = new real_t[250 * 1024];

    for (int x = 0; x < 250 * 1024; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    for (int x = 0; x < 250; ++x){
        for (int y = 0; y < 1024; ++y){
            c[x * 1024 + y] = a[x * 1024 + y] + b[x * 1024 + y];
        }
    }


    #pragma acc data copyin(a[0:250*1024], b[0:250*1024]) copyout(c[0:250*1024])
    {
        #pragma acc parallel loop worker
        for (int x = 0; x < 250; ++x){
            #pragma acc loop worker
            for (int y = 0; y < 1024; ++y){
                c[x * 1024 + y] = a[x * 1024 + y] + b[x * 1024 + y];
            }
        }
    }

    for (int x = 0; x < 250 * 1024; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
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