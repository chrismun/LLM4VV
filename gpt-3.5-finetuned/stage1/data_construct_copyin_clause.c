#include "acc_testsuite.h"
#ifndef T1
//T1:data construct copyin clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));
    real_t * e = (real_t *)malloc(n * sizeof(real_t));
    real_t * f = (real_t *)malloc(n * sizeof(real_t));
    real_t * g = (real_t *)malloc(n * sizeof(real_t));
    real_t * h = (real_t *)malloc(n * sizeof(real_t));
    real_t * i = (real_t *)malloc(n * sizeof(real_t));
    real_t * j = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
        c[x] = 0;
        d[x] = rand() / (real_t)(RAND_MAX / 10);
        e[x] = 0;
        f[x] = 0;
        g[x] = rand() / (real_t)(RAND_MAX / 10);
        h[x] = 0;
        i[x] = 0;
        j[x] = 0;
    }

    #pragma acc data copyin(a[0:n], d[0:n], g[0:n]) copyout(b[0:n], e[0:n], h[0:n]) copyout(c[0:n], f[0:n], i[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x] + d[x] + g[x];
            }
        }
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                e[x] = b[x] + d[x] + g[x];
            }
        }
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                h[x] = e[x] + a[x] + g[x];
            }
        }
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = f[x] + i[x];
            }
        }
    }

    real_t temp = 0;
    for (int x = 0; x < n; ++x){
        temp = 0;
        for (int y = 0; y < 10; ++y){
            temp = temp + a[x] + d[x] + g[x];
        }
        if (fabs(b[x] - temp) > PRECISION){
            err += 1;
        }

        temp = 0;
        for (int y = 0; y < 10; ++y){
            temp = temp + a[x] + d[x] + g[x] + d[x] + g[x];
        }
        if (fabs(e[x] - temp) > PRECISION){
            err += 1;
        }

        temp = 0;
        for (int y = 0; y < 10; ++y){
            temp = temp + a[x] + d[x] + g[x] + a[x] + g[x];
        }
        if (fabs(h[x] - temp) > PRECISION){
            err += 1;
        }
        
        if (fabs(c[x]) > PRECISION){ //Should be zero
            err += 1;
        }
        if (fabs(f[x]) > PRECISION){ //Should be zero
            err += 1;
        }
        if (fabs(i[x]) > PRECISION){ //Should be zero
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