#include "acc_testsuite.h"
#ifndef T1
//T1:compute,reduction,V:1.0-2.7
int test1(){
    int err = 0;

    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    real_t reduction_result = 0;

    #pragma acc parallel compute reduction(+:reduction_result)
    {
        #pragma acc loop
        for (int x = 0; x < n; ++x){
            c[x] = a[x] + b[x];
            reduction_result += c[x];
        }
    }

    real_t expected_result = 0;
    for (int x = 0; x < n; ++x){
        expected_result += a[x] + b[x];
    }

    if (fabs(reduction_result - expected_result) > PRECISION){
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