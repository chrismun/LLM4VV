#include "acc_testsuite.h"
#ifndef T1
//T1:host_data construct use_device clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *a_host = (real_t *)malloc(n * sizeof(real_t));
    real_t *b_host = (real_t *)malloc(n * sizeof(real_t));
    real_t *c_host = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
        a_host[x] = a[x];
        b_host[x] = b[x];
        c_host[x] = 0.0;
    }

    #pragma acc host_data use_device(a, b, c)
    {
        #pragma acc parallel
        {
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        c_host[x] = a_host[x] + b_host[x];
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c_host[x] - c[x]) > PRECISION){
            err = 1;
        }
    }

    free(a);
    free(b);
    free(c);
    free(a_host);
    free(b_host);
    free(c_host);

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