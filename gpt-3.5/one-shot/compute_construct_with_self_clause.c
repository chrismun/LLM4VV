#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,data,compute,self,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = (real_t)rand() / (real_t)(RAND_MAX / 10);
        b[x] = (real_t)rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0.0;
        d[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n]) create(d[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                d[x] = a[x] + b[x];
            }

            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = d[x] * d[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        real_t expected = (a[x] + b[x]) * (a[x] + b[x]);
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