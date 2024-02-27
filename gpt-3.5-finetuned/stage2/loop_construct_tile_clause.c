#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct tile clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t **a = (real_t **)malloc(n * sizeof(real_t *));
    real_t **b = (real_t **)malloc(n * sizeof(real_t *));
    real_t **c = (real_t **)malloc(n * sizeof(real_t *));

    for (int x = 0; x < n; ++x){
        a[x] = (real_t *)malloc(n * sizeof(real_t));
        b[x] = (real_t *)malloc(n * sizeof(real_t));
        c[x] = (real_t *)malloc(n * sizeof(real_t));
        for (int y = 0; y < n; ++y){
            a[x][y] = rand() / (real_t)(RAND_MAX / 10);
            b[x][y] = rand() / (real_t)(RAND_MAX / 10);
            c[x][y] = 0.0;
        }
    }

    #pragma acc data copyin(a[0:n][0:n], b[0:n][0:n]) copyout(c[0:n][0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop tile(4, 2)
            for (int x = 0; x < n; ++x){
                for (int y = 0; y < n; ++y){
                    c[x][y] = c[x][y] + a[x][y] * b[y][x];
                }
            }
        }
    }

    for (int x = 0; x < n; ++x){
        for (int y = 0; y < n; ++y){
            if (fabs(c[x][y] - (a[x][y] * b[y][x])) > PRECISION){
                err = 1;
            }
        }
    }

    for (int x = 0; x < n; ++x){
        free(a[x]);
        free(b[x]);
        free(c[x]);
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