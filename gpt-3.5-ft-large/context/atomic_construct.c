#include "acc_testsuite.h"
#ifndef T1
//T1:atomic,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *totals = (real_t *)malloc(10 * sizeof(real_t));
    real_t *totals_comparison = (real_t *)malloc(10 * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
    }
    for (int x = 0; x < 10; ++x){
        totals[x] = 0;
        totals_comparison[x] = 0;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copy(totals[0:10]) copyout(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                #pragma acc atomic
                    c[x] = a[x] + b[x];
                #pragma acc atomic
                    totals[x%10] = c[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        totals_comparison[x%10] += a[x] + b[x];
    }
    for (int x = 0; x < 10; ++x){
        if (fabs(totals_comparison[x] - totals[x]) > PRECISION){
            err += 1;
            break;
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x]))) > PRECISION){
            err += 1;
            break;
        }
    }

    return err;
}
#endif

#ifndef T2
//T2:atomic,construct-independent,devonly,V:2.0-2.7
int test2(){
    // DOES NOT SUPPORT THE POW FUNCTION
    return 0;
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *totals = (real_t *)malloc(10 * sizeof(real_t));
    real_t *totals_comparison = (real_t *)malloc(10 * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
    }

    for (int x = 0; x < 10; ++x){
        totals[x] = 1;
        totals_comparison[x] = 1;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copy(totals[0:10]) copyout(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                #pragma acc atomic
                c[x] = a[x] + b[x];
                #pragma acc atomic
                totals[x%10] = totals[x%10] * c[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
	totals_comparison[x%10] = 1;

        for (int y = 0; y <= x; ++y){
              totals_comparison[y%10] = totals_comparison[y%10] * (a[y] + b[y]);
        }

        if (fabs(totals_comparison[x%10] - totals[x%10]) > PRECISION){
            err += 1;
        }
    }
    return err;
}
#endif

#ifndef T3
//T3:atomic,construct-independent,devonly,combined-constructs,V:2.0-2.7
int test3(){
    // DOES NOT SUPPORT THE POW FUNCTION
    return 0;