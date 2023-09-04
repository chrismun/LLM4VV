#include "acc_testsuite.h"
#ifndef T2
//T2:parallel,loop,loop-interchange,V:1.0-2.7
int test2(){
    int err = 0;

    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = rand() / (real_t)(RAND_MAX / 10);
        d[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc kernels
        #pragma acc loop gang num_gangs(16)
        for (int x = 0; x < n; ++x){
            d[x] = a[x] + b[x] + c[x];
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(d[x] - (a[x] + b[x] + c[x])) > PRECISION){
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