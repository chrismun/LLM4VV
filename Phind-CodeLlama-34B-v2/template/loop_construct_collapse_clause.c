#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct collapse clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(10 * N * sizeof(real_t));
    real_t * b = (real_t *)malloc(10 * N * sizeof(real_t));

    for (int x = 0; x < 10 * N; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
    }

    #pragma acc data copy(a[0:10*N], b[0:10*N])
    {
        #pragma acc parallel loop collapse(2)
        for (int i = 0; i < 10; ++i){
            for (int j = 0; j < N; ++j){
                b[i * N + j] = a[i * N + j] * 2.0;
            }
        }
    }

    for (int i = 0; i < 10; ++i){
        for (int j = 0; j < N; ++j){
            if (fabs(b[i * N + j] - (a[i * N + j] * 2.0)) > PRECISION){
                err += 1;
            }
        }
    }

    free(a);
    free(b);

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