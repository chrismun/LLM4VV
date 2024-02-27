#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t tmp = 0;

    for (int x = 0; x < n; ++x){
        a[x] = 1000 * rand() / (real_t)(RAND_MAX);
        b[x] = 1000 * rand() / (real_t)(RAND_MAX);
    }

    #pragma acc loop private(tmp)
    for (int x = 0; x < n; ++x){
        tmp = a[x] + b[x];
        a[x] = tmp/2.0;
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (b[x] + a[x])/2) > PRECISION){
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