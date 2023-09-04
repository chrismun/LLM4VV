#include "acc_testsuite.h"
#ifndef T1
//T1:loop,reduction,V:1.0-2.7
int test1(){

    int err = 0;
    srand(SEED);

    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t final_sum = 0.0;
    real_t sum = 0.0;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copy(c[0:n])
    {
        #pragma acc parallel loop reduction(+:sum)
        for (int x = 0; x < n; ++x){
            c[x] = a[x] + b[x];
            sum += c[x];
        }

        #pragma acc parallel loop reduction(+:final_sum)
        for (int x = 0; x < n; ++x){
            final_sum += c[x];
        }
    }

    real_t host_sum = 0.0;
    real_t host_final_sum = 0.0;

    for (int x = 0; x < n; ++x){
        host_sum += c[x];
        host_final_sum += c[x];
    }

    if (fabs(host_sum - sum) > PRECISION){
        err += 1;
    }

    if (fabs(host_final_sum - final_sum) > PRECISION){
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