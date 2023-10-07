#include "acc_testsuite.h"
#ifndef T1
/*T1:serial construct self clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * sum = (real_t *)malloc(n * sizeof(real_t));
    real_t * sum_host = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        sum[x] = 0.0;
        sum_host[x] = a[x] + b[x];
    }

    #pragma acc data copy(a[0:n], b[0:n], sum[0:n])
    {
        #pragma acc parallel present(a[0:n], b[0:n], sum[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                sum[x] = a[x] + b[x];
            }
        }

        #pragma acc serial self
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                sum[x] += 1;
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(sum[x] - sum_host[x] - 1) > PRECISION){
            err = 1;
        }
    }

    free(a);
    free(b);
    free(sum);
    free(sum_host);

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