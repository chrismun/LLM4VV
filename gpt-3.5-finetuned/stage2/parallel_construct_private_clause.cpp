#include "acc_testsuite.h"
#ifndef T1
//T1:parallel construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = new real_t[10 * n];
    real_t *b = new real_t[10 * n];
    real_t *c = new real_t[10];

    for (int y = 0; y < 10; ++y){
        for (int x = 0; x < n; ++x){
            a[y * n + x] = rand() / (real_t)(RAND_MAX / 10);
            b[y * n + x] = rand() / (real_t)(RAND_MAX / 10);
        }
        c[y] = 1000;
    }

    #pragma acc data copyin(a[0:10*n], b[0:10*n]) copy(c[0:10])
    {
        #pragma acc parallel loop private(c[0:10])
        for (int x = 0; x < 10; ++x){
            for (int y = 0; y < n; ++y){
                c[x] += a[x * n + y] + b[x * n + y];
            }
        }
    }

    for (int x = 0; x < 10; ++x){
        if (fabs(c[x] - 1000) > (2 * PRECISION)){
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