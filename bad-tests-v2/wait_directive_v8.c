#include "acc_testsuite.h"
#ifndef T1
//T1:wait,construct-independent,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    unsigned int a_update = 1;
    #pragma acc data copyin(a[0:n]) create(a_update)
    {
        #pragma acc parallel
        {
            if (a[0] == a[0]) {
                #pragma acc loop
                for (int x = 0; x < n; ++x){
                    a[x] = a[x] + 2;
                }
            }
            #pragma acc wait
            if (a[0] == a[0]) {
                for (int x = 0; x < n; ++x){
                    a[x] = a[x] + 2;
                }
            }
            a_update = 0;
        }
    }
    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - (real_t)(2 * n + 2)) > PRECISION) {
            err = 1;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:wait,construct-independent,dependence,V:1.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));
    real_t * e = (real_t *)malloc(n * sizeof(real_t));
    real_t * f = (real_t *)malloc(n * sizeof(real_t));
    real_t error;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    unsigned int a_update = 1;
    #pragma acc data copyin(a[0:n], b[0:n], c[0:n]) copy(e[0:n])
    {
        #pragma acc parallel present(e[0:n]) create(a_update)
        {
            if (e[0] == e[0]) {
                #pragma acc loop 
                for (int x = 0; x < n; ++x){
                    e[x] = a[x] + b[x];
                }
            }
        }
        #pragma acc parallel present(e[0:n]) create(a_update)
        {
            if (a[0] == a[0]) {
                #pragma acc loop 
                for (int x = 0; x < n; ++x){
                    e[x] = e[x] + c[x];
                }
            }
            #pragma acc wait
            if (e[0] == e[0]) {
                #pragma acc parallel loop present(a[0:n], c[0:n]) create(d[0:n])
                for (int x = 0; x < n; ++x){
                        d[x] = a[x] + c[x];
                }
                for (int x = 0; x < n; ++x){
                    e[x] = e[x] + d[x];
                }
            }
            #pragma acc wait
            if (e[0] == e[0]) {
                #pragma acc parallel loop present(d[0:n]) create(f[0:n])
                for (int x = 0; x < n; ++x){
                        f[x] = d[x] + 1;
                }
                for (int x = 0; x < n; ++x){
                    e[x] = e[x] + f[x];
                }
            }
            a_update = 0;
        }
    }
    for (int x = 0; x < n; ++x){
        error = (e[x] - (((a[x] + b[x]) + a[x] + c[x]) + (a[x] + c[x] + 1))) / (((a[x] + b[x]) + a[x] + c[x]) + (a[x] + c[x] + 1));
        if (fabs(error) != error || error > PRECISION) {
            err = 1;
        }
    }

    return err;
}
#endif

#ifndef T3
//T3:wait,construct-independent,loop,region,V:1.0-2.7
int test3(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * b = (real_t *)malloc(10 * n * sizeof(real_t));
    real_t * c = (real_t *)malloc(10 * n * sizeof(real_t));

    for (int x = 0; x < 10 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    unsigned int a_update = 1;
    real_t accum;
    #pragma acc data copyin(a[0:10*n], b[0:10*n]) create(c[0:10*n], a_update)
    {
        for (int x = 0; x < n; ++x){
            accum = 0;
            #pragma acc parallel present(c[0:10*n]) create(accum)
            {
                #pragma acc loop 
                for (int y = 0; y < 10; ++y){
                    accum = accum + a[10 * x + y] * b[10 * x + y];
                }
            }
            accum = accum / 10;
            #pragma acc parallel present(c[0:10*n]) create(a_update)
            {
                #pragma acc loop 
                for (int y = 0; y < 10; ++y){
                    c[10 * x + y] = accum;
                }
                #pragma acc wait(2)
            }
            if (c[x] != accum || c[n + x] != accum || c[2 * n + x] != accum || c[3 * n
            + x] != accum || c[4 * n + x] != accum || c[5 * n + x] != accum || c[6 * n + x] !=
            accum || c[7 * n + x] != accum || c[8 * n + x] != accum || c[9 * n + x] !=
            accum){
                err = 1;
            }
        }
        #pragma acc parallel 
        for (int x = 0; x < 10 * n; ++x){
            a[x] = 0;
        }
    }

    return 0;