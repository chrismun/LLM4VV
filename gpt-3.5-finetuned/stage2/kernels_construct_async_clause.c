#include "acc_testsuite.h"
#ifndef T1
//T1:kernels construct async clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *d = (real_t *)malloc(n * sizeof(real_t));
    real_t *e = (real_t *)malloc(n * sizeof(real_t));
    real_t *f = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
        d[x] = rand() / (real_t)(RAND_MAX / 10);
        e[x] = rand() / (real_t)(RAND_MAX / 10);
        f[x] = 0.0;
    }

    #pragma acc enter data copyin(a[0:n], b[0:n], d[0:n], e[0:n], c[0:n], f[0:n])

    #pragma acc kernels loop present(a[0:n], b[0:n], c[0:n]) async(1)
    for (int x = 0; x < n; ++x){
        c[x] = a[x] + b[x];
    }

    #pragma acc kernels loop present(d[0:n], e[0:n], f[0:n]) async(2)
    for (int x = 0; x < n; ++x){
        f[x] = d[x] + e[x];
    }

    #pragma acc wait
    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err += 1;
        }
        if (fabs(f[x] - (d[x] + e[x])) > PRECISION){
            err += 1;
        }
    }

    #pragma acc exit data delete(a[0:n], b[0:n], d[0:n], e[0:n]) copyout(c[0:n], f[0:n])

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