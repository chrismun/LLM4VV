#include "acc_testsuite.h"
#ifndef T1
//T1:kernels construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = new real_t[10 * n];
    real_t *a_copy = new real_t[10 * n];
    real_t *b = new real_t[10 * n];
    real_t *b_copy = new real_t[10 * n];
    real_t *c = new real_t[n];
    real_t *c_copy = new real_t[n];
    real_t *d = new real_t[n];
    real_t *d_copy = new real_t[n];

    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < n; ++y){
            a[x * n + y] = rand() / (real_t)(RAND_MAX / 10);
            b[x * n + y] = rand() / (real_t)(RAND_MAX / 10);
            c[y] = 0.0;
            d[y] = 0.0;
            a_copy[x * n + y] = a[x * n + y];
            b_copy[x * n + y] = b[x * n + y];
            c_copy[y] = c[y];
            d_copy[y] = d[y];
        }
    }

    #pragma acc data copyin(a[0:10*n], b[0:10*n]) copyout(c[0:n], d[0:n])
    {
        #pragma acc kernels loop gang private(c)
        for (int x = 0; x < 10; ++x){
            #pragma acc loop worker private(c)
            for (int y = 0; y < n; ++y){
                c[y] = a[x * n + y] + b[x * n + y];
            }
        }
        #pragma acc kernels loop gang private(c)
        for (int x = 0; x < 10; ++x){
            #pragma acc loop worker private(c)
            for (int y = 0; y < n; ++y){
                d[y] = a[x * n + y] + b[x * n + y];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - c_copy[x]) > PRECISION){
            err += 1;
        }
        if (fabs(d[x] - d_copy[x]) > PRECISION){
            err += 1;
        }
    }

    for (int x = 0; x < 10; ++x){
        for (int y = 0; y < n; ++y){
            a[x * n + y] = a_copy[x * n + y];
            b[x * n + y] = b_copy[x * n + y];
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