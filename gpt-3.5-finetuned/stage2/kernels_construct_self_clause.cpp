#include "acc_testsuite.h"
#ifndef T1
//T1:kernels,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = new real_t[1024 * n];
    real_t *b = new real_t[1024 * n];
    real_t *c = new real_t[1024 * n];
    real_t *d = new real_t[1024 * n];

    for (int x = 0; x < 1024 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
        d[x] = 0.0;
    }

    #pragma acc data copyin(a[0:1024*n], b[0:1024*n]) copy(c[0:1024*n]) 
        #pragma acc kernels loop gang independent
        for (int x = 0; x < 1024; ++x){
            for (int y = 0; y < n; ++y){
                c[x * n + y] = a[x * n + y] + b[x * n + y];
            }
        }

    #pragma acc data copy(c[0:1024*n]) copyout(d[0:1024*n])
        #pragma acc kernels loop gang independent
        for (int x = 0; x < 1024; ++x){
            for (int y = 0; y < n; ++y){
                d[x * n + y] = c[x * n + y] * 2;
            }
        }

    for (int x = 0; x < 1024; ++x){
        for (int y = 0; y < n; ++y){
            if (fabs(a[x * n + y] + b[x * n + y] - c[x * n + y]) > PRECISION){
                err = 1;
            }
            if (fabs(c[x * n + y] * 2 - d[x * n + y]) > PRECISION){
                err = 1;
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