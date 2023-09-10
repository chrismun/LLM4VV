#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct collapse clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = new real_t[10 * n];
    real_t * b = new real_t[10 * n];
    real_t * c = new real_t[10 * n];

    for(int x = 0; x < 10 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc data copyin(a[0:10*n], b[0:10*n]) copy(c[0:10*n])
    {
        #pragma acc parallel
        {
            #pragma acc loop collapse(2)
            for (int x1 = 0; x1 < n; ++x1){
              for (int x2 = 0; x2 < n; ++x2){
                  c[(n * x1) + x2] = a[(n * x1) + x2] + b[(n * x1) + x2];
              }
            }
        }
    }

    for (int x = 0; x < 10 * n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err = 1;
        }
    }

    return err
}
#endif

#ifndef T2
//T1:loop construct collapse clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = new real_t[20 * n];
    real_t * b = new real_t[20 * n];
    real_t * c = new real_t[20 * n]();

    for(int x = 0; x < 20 * n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }
    int hosterrcpu = 0;
    #pragma acc data copyin(a[0:20*n], b[0:20*n]) copy(c[0:20*n])
    {
        #pragma acc parallel
        {
            #pragma acc loop independent collapse(2)
            for(int x = 0; x < 10; ++x){
                for(int y = 0; y < 2 * n; ++y){
                    c[(2 * n * x) + y] = a[(2 * n* x) + y] + b[(2 * n * x) + y];
                }
            }
            #pragma acc loop independent collapse(2)
            for(int x = 10; x < 20; ++x){
                for(int y = 0; y < n; ++y){
                    c[(2 * n * x) + y] = a[(2 * n* x) + y] + b[(2 * n * x) + y];
                }
            }
        }
    }

    for(int x = 0; x < 20 * n; ++x){
        if(fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err++;
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