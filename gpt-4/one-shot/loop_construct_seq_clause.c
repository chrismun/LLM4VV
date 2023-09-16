#include "acc_testsuite.h"

#ifndef T1
//T1:kernels,loop,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t dot_product = 0.0;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc kernels
    {
        #pragma acc loop seq
        for (int x = 0; x < n; ++x){
            dot_product += a[x] * a[x]; // Simple dot-product operation for demonstration.
        }
    }

    real_t expected_dot_product = 0.0;
    for (int x = 0; x < n; ++x){
        expected_dot_product += a[x] * a[x];
    }

    if (fabs(dot_product - expected_dot_product) > PRECISION){
            err += 1;
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