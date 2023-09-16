#include "acc_testsuite.h"
#ifndef T2
//T2:kernels,data,data-region,V:2.0-2.7
int test2(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t total = 0.0;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copyin(a[0:n]) copy(total)
    {
        #pragma acc kernels loop reduction(+:total)
        for (int x = 0; x < n; ++x){
            total += a[x];
        }
    }

    real_t host_total = 0.0;
    for (int x = 0; x < n; ++x){
        host_total += a[x];
    }

    if (fabs(total - host_total) > PRECISION){
        err = 1;
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