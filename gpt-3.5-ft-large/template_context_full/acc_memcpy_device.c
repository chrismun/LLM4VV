#include "acc_testsuite.h"
#ifndef T1
//T1: acc memcpy device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));
    real_t *d_a = (real_t *)malloc(n * sizeof(real_t));
    real_t *d_b = (real_t *)malloc(n * sizeof(real_t));
    real_t *d_c = (real_t *)malloc(n * sizeof(real_t));
    int data_err;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    #pragma acc enter data create(c[0:n])

    for (int x = 0; x < n; ++x){
        d_c[x] = c[x];
    }
    acc_deviceptr_t dev_ptr = acc_copyin(c, n * sizeof(real_t));
    d_c = dev_ptr;
    acc_detach(c);

    #pragma acc data copyin(a[0:n], b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                d_c[x] += a[x] + b[x];
            }
        }
        #pragma acc exit data copyout(c[0:n])
    }

    #pragma acc wait

    data_err = 0;
    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x]))) {
            data_err += 1;
        }
    }
    #pragma acc exit data delete(d_a[0:n], d_b[0:n], c[0:n])
    
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