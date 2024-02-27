#include "acc_testsuite.h"
#ifndef T1
//T1:compute construct vector_length clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 1 + rand() / (real_t)(RAND_MAX / 10);
        b[x] = 1 + rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    int _n_ = n;
    #pragma acc data copyin(a[0:_n_], b[0:_n_]) copyout(c[0:_n_])
    {
        #pragma acc compute vector_length(16) 
        {
            #pragma acc loop vector
            for (int x = 0; x < _n_; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < _n_; ++x){
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