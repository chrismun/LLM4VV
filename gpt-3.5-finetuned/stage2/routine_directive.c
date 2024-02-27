#include "acc_testsuite.h"
#ifndef T1
//T1:routine directive,V:2.7-3.3
void f(real_t *a, real_t *b){
    #pragma acc loop seq
    for (int x = 0; x < n; ++x){
        a[x] = log(a[x]);
    }
}

int test1(){
    int err = 0;
    srand(SEED);
    real_t * a = (real_t *)malloc(n * sizeof(real_t));
    real_t * b = (real_t *)malloc(n * sizeof(real_t));
    real_t * c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = a[x];
        c[x] = 1;
    }

    #pragma acc data copyin(b[0:n]) copyout(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop gang worker vector
            for (int x = 0; x < n; ++x){
                c[x] *= b[x];
            }
        }
    }

    #pragma acc routine f(b,c)
    #pragma acc data copyin(a[0:n]) copyout(c[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop gang worker vector
            for (int x = 0; x < n; ++x){
                c[x] *= a[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - a[x] * b[x]) > PRECISION){
            err += 1;
            break;
        }
    }

    free(a);
    free(b);
    free(c);

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