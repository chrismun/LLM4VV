#include "acc_testsuite.h"
#ifndef T2
//T2:kernels,data,data-region,devptr,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)acc_malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc data deviceptr(a, b)
    {
        #pragma acc kernels present(a, b, d[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                d[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(d[x] - (a[x] + b[x])) > PRECISION){
            err += 1;
        }
    }

    acc_free(d);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif
    return failcode;
}