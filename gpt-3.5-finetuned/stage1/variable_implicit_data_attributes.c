#include "acc_testsuite.h"
#ifndef T1
//T1:variable implicit data attributes,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int l = n;

    real_t * a = (real_t *)malloc(l * sizeof(real_t));
    real_t * b = (real_t *)malloc(l * sizeof(real_t));
    real_t * c = (real_t *)malloc(l * sizeof(real_t));
    real_t *b_host = (real_t *)malloc(n * sizeof(real_t));
    real_t *c_host = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
        b_host[x] = b[x];
        c_host[x] = 0;
    }

    #pragma acc data copyin(a[0:l], b[0:l]) copyout(c[0:l])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c_host[x] - c[x]) > PRECISION){
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