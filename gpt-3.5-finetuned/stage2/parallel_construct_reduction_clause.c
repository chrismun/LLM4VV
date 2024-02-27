#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,parallel,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t *_Complex a = (real_t*)_Complex  malloc(n * sizeof(real_t));
    real_t *_Complex b = (real_t*)_Complex  malloc(n * sizeof(real_t));
    real_t *_Complex c = (real_t*)_Complex  malloc(n * sizeof(real_t));
    real_t max = 0.0;

    for (int x = 0; x < n; ++x){
        a[x] = 1 + 1 * _Complex_I * rand() / (real_t)(RAND_MAX / 10);
        b[x] = 1 + 1 * _Complex_I * rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0 + 0.0 * _Complex_I;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copy(c[0:n])
    {
        #pragma acc parallel reduction(max:c)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err = 1;
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