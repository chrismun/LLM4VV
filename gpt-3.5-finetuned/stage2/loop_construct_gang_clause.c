#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct gang clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = (real_t *)malloc(n * 1024 * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[1024 * x] = 0;
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
    }


    #pragma acc data copyin(b[0:n]) copyout(c[0:n]) copy(a[0:n*1024])
    {
        #pragma acc parallel loop gang
        for (int x = 0; x < n; ++x){
            for (int y = 0; y < 1024; ++y){
                a[1024 * x] = a[1024 * x] + b[x];
            }
            c[x] = a[1024 * x];
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - 1024 * b[x]) > PRECISION){
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