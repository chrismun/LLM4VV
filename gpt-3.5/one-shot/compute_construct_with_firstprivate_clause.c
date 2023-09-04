#include "acc_testsuite.h"

#ifndef T1
//T1:parallel,compute,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));
    real_t * d = (real_t *)malloc(n * sizeof(real_t));

    real_t scalar = rand() / (real_t)(RAND_MAX / 10);

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
        c[x] = 0.0;
        d[x] = 0.0;
    }

    #pragma acc data copyin(a[0:n]), copy(b[0:n]), copyout(c[0:n]), copy(d[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop independent
            for (int x = 0; x < n; ++x){
                b[x] = a[x] + scalar;
            }

            #pragma acc loop independent reduction(+:c)
            for (int x = 0; x < n; ++x){
                c[x] = b[x] + scalar;
            }

            #pragma acc loop independent firstprivate(scalar)
            for (int x = 0; x < n; ++x){
                d[x] = c[x] + scalar;
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(d[x] - (a[x] + (scalar * 3))) > PRECISION){
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