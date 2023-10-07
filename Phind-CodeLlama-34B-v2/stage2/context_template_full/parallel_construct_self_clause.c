#include "acc_testsuite.h"
#ifndef T1
/*T1:parallel construct self clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * sum_host = (real_t *)malloc(n * sizeof(real_t));
    real_t * sum_device = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        sum_host[x] = a[x] + b[x];
        sum_device[x] = 0.0;
    }

    #pragma acc data copy(a[0:n], b[0:n], sum_device[0:n])
    {
        #pragma acc parallel self(acc_device_nvidia)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                sum_device[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(sum_device[x] - sum_host[x]) > PRECISION){
            err = 1;
        }
    }

    free(a);
    free(b);
    free(sum_host);
    free(sum_device);

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