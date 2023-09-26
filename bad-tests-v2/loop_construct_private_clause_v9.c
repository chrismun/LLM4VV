#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t ** a = (real_t **)malloc(n * sizeof(real_t *));
    real_t ** a_copy = (real_t **)malloc(n * sizeof(real_t *));
    real_t * a_init = (real_t *)malloc(n * n * sizeof(real_t));
    real_t ** b = (real_t **)malloc(n * sizeof(real_t *));
    real_t ** c = (real_t **)malloc(n * sizeof(real_t *));
    int host_a = 1;

    for (int x = 0; x < n; ++x){
        for (int y = 0; y < n; ++y){
            a_init[x * n + y] = rand() / (real_t)(RAND_MAX / 10);
            b[x][y] = rand() / (real_t)(RAND_MAX / 10);
            c[x][y] = rand() / (real_t)(RAND_MAX / 10);
        }
    }

    #pragma acc data copyin(b[0:n][0:n], c[0:n][0:n]) copy(a[0:n][0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop gang private(a_copy, host_a)
            for (int x = 0; x < n; ++x){
                a_copy = a[x];
                host_a = 1;
                #pragma acc loop worker vector private(host_a)
                for (int y = 0; y < n; ++y){
                    a[x][y] = b[x][y] + c[x][y] + host_a;
                    host_a = 0;
                }
                #pragma acc loop worker vector
                for (int y = 0; y < n; ++y){
                    a[x][y] = (a[x][y] + c[x][y]) / a[x][y];
                }
            }
        }
    }

    real_t error = 0.0;
    for (int x = 0; x < n; ++x){
        for (int y = 0; y < n; ++y){
            error = error + fabs(a_init[x * n + y] - a[x][y]);
        }
    }

    if (error > (n * n * 2 * PRECISION)){
        err = 1;
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