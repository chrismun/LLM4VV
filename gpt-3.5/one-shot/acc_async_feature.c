#include "acc_testsuite.h"

#ifndef T1
//T1:parallel,data,data-region,V:2.6-2.8
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
        c[x] = 0.0;
        d[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n]) copyout(b[0:n]) create(c[0:n]) present(d[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }

            #pragma acc loop collapse(2) async
            for (int x = 0; x < n; ++x){
                for (int y = 0; y < n; ++y){
                    d[x] += a[y] * c[x];
                }
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION || fabs(d[x] - (a[0] * c[x] + a[1] * c[x] + a[2] * c[x])) > PRECISION){
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