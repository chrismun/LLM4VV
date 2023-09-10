#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct vector clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 1; x < n; ++x){
        a[x] = 1;
    a[0] = n - 3;

        b[x] = 0.0;
    b[0] = 2.0;
    }

    #pragma acc data copy(a[0:n]) copyout(b[0:n])
    {
    #pragma acc serial
        {
        #pragma acc loop vector
        for (int x = 0; x < n; ++x){
            b[x] = a[x];
        }
        }
        #pragma acc update host(b[0:n])
    }

    for (int x = 0; x < n; ++x){
        if (fabs(b[x] - a[x]) > PRECISION){
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