#include "acc_testsuite.h"
#ifndef T1
//T1:serial,construct,loop,V:2.6-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t **a = (real_t **)malloc(n * sizeof(real_t *));
    real_t **b = (real_t **)malloc(n * sizeof(real_t *));

    for(int x = 0; x < n; ++x){
        a[x] = (real_t *)malloc(n * sizeof(real_t));
        b[x] = (real_t *)malloc(n * sizeof(real_t));
    }

    for (int y = 0; y < n; ++y){
        for (int x = 0; x < n; ++x){
            a[y][x] = rand() / (real_t)(RAND_MAX / 10);
            b[y][x] = 0;
        }
    }

    #pragma acc data copyin(a[0:n][0:n]) copyout(b[0:n][0:n])
    {
        #pragma acc serial vector_length(16)
        {
            #pragma acc loop vector
            for (int y = 0; y < n; ++y){
                for (int x = 0; x < n; ++x){
                    b[y][x] = a[y][x];
                }
            }
        }
    }

    for (int y = 0; y < n; ++y){
        for (int x = 0; x < n; ++x){
            if (fabs(b[y][x] - a[y][x]) > PRECISION){
                err += 1;
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