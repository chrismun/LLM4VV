#include "acc_testsuite.h"

#ifndef T1
//T1:parallel,reference-counting,V:2.5-3.1
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));

    #pragma acc data copyin(a[0:n])
    {
        for (int i = 0; i < n; ++i){
            a[i] = rand() / (real_t)(RAND_MAX / 10);
            b[i] = rand() / (real_t)(RAND_MAX / 10);
            c[i] = 0.0;
        }

        #pragma acc parallel
        {
            #pragma acc loop independent
            for (int i = 0; i < n; ++i){
                c[i] = a[i] + b[i];
            }
        }
    }

    for (int i = 0; i < n; ++i){
        if (fabs(c[i] - (a[i] + b[i])) > PRECISION){
            err += 1;
            break;
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
    for (int i = 0; i < NUM_TEST_CALLS; ++i){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}