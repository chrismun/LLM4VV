#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct reduction clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    real_t acc_sum = 0.0;
    real_t host_sum = 0.0;

    #pragma acc data copy(a[0:n], b[0:n])
    {
        #pragma acc parallel loop reduction(+:acc_sum)
        for (int x = 0; x < n; ++x){
            acc_sum += a[x] * b[x];
        }
    }

    for (int x = 0; x < n; ++x){
        host_sum += a[x] * b[x];
    }

    if (fabs(acc_sum - host_sum) > PRECISION){
        err = 1;
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