#include "acc_testsuite.h"
#ifndef T1
//T1:loop,data,data-region,V:2.6
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = x;
        c[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n])
    {
        #pragma acc parallel loop copyin(a[0:n]) private(b[0:n])
        for (int x = 0; x < n; ++x){
                b[x] = a[x];
                c[x] = b[x] * b[x];
        }
    }
    #pragma acc update host(c[0:n])

    for (int x = 0; x < n; ++x){
        real_t expected = a[x] * a[x];
        if (fabs(c[x] - expected) > PRECISION){
            err += 1;
            break;
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