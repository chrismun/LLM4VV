#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct worker clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t * restrict a = new real_t[n];
    real_t * restrict b = new real_t[n];

    for (int x= 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0.0;
    }

    #pragma acc data copyin(a[n:n], a[0]) copyout(b[n:n], b[0])
    {
        #pragma acc parallel
        {
            #pragma acc loop worker
            for (int x = 1; x < n - 1; ++x){
                b[x] = a[x - 1] + a[x] + a[x + 1];
            }
        }
    }

    for (int x = 1; x < n - 1; ++x){
        if (fabs(b[x] - (a[x - 1] + a[x] + a[x + 1])) > PRECISION){
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