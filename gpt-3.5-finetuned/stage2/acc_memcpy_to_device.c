#include "acc_testsuite.h"
#ifndef T1
//T1:acc memcpy to device,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d;

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
    }

    d = acc_copyin(a, n * sizeof(real_t));
    acc_memcpy_to_device(d, b, n * sizeof(real_t));

    #pragma acc data deviceptr(d)
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                d[x] = d[x] * d[x];
            }
        }
    }

    acc_memcpy_from_device(c, d, n * sizeof(real_t));
    acc_delete(d);

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] * a[x])) > PRECISION){
            err = 1;
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