#include "acc_testsuite.h"
#ifndef T1
//T1:acc memcpy to device,V:2.7-3.3
int test1(){
    int err = 0;
    size_t array_size = n * sizeof(real_t);
    real_t *a = (real_t *)malloc(array_size);
    real_t *b = (real_t *)malloc(array_size);
    real_t *c = (real_t *)malloc(array_size);
    real_t *a_host = (real_t *)malloc(array_size);
    real_t *b_host = (real_t *)malloc(array_size);

    for (int x = 0; x < n; ++x){
        a_host[x] = rand() / (real_t)(RAND_MAX / 10);
        b_host[x] = rand() / (real_t)(RAND_MAX / 10);
    }

    for (int x = 0; x < n; ++x){
        a[x] = 0.0;
        b[x] = 0.0;
        c[x] = 0.0;
    }

    for (int x = 0; x < n; ++x){
        a[x] = a_host[x];
    }
    acc_memcpy_to_device(a, b_host, n * sizeof(real_t));
    #pragma acc data copyin(a[0:n], b[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - a_host[x]) > PRECISION){
            err += 1;
        }
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