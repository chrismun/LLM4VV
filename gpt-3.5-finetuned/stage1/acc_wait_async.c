#include "acc_testsuite.h"
#ifndef T1
//T1:acc wait async,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(SEED / 10);
        b[x] = a[x];
    }

#pragma acc enter data create(a[0:n])
    // complete test here
#pragma acc parallel loop present(b[0:n])
    for (int x = 0; x < n; ++x){
        b[x] = fabs(b[x]);
    }
    acc_wait_async(n, 0);
#pragma acc update device(a[0:n]) async(0)
    for (int x = 0; x < n; ++x){
        if (a[x] > PRECISION){
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