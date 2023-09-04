#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,data,data-region,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
    }

    real_t * dev_a = (real_t *)malloc(n * sizeof(real_t));
    real_t * dev_b = (real_t *)malloc(n * sizeof(real_t));

    #pragma acc data copyin(a[0:n]) create(dev_a[0:n], dev_b[0:n])
    {
        #pragma acc parallel deviceptr(dev_a, dev_b)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                dev_a[x] = a[x];
                dev_b[x] = 0.0;
            }
        }
    }

    #pragma acc data copyout(b[0:n]) delete(dev_a[0:n], dev_b[0:n])
    {
        #pragma acc parallel deviceptr(dev_a, dev_b)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = dev_b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - b[x]) > PRECISION){
            err += 1;
            break;
        }
    }

    free(dev_a);
    free(dev_b);
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