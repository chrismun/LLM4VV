#include "acc_testsuite.h"
#ifndef T1
//T1:data construct delete clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t *a = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = 3.3;
    }

    #pragma acc enter data create(a[0:n])
    #pragma acc parallel present(a[0:n])
    {
        #pragma loop count(4)
        for (int x = 0; x < 5; ++x){
            a[x] += 1;
        }
    }
    #pragma acc exit data delete(a[0:n]) copyout(a[0:n])

    for (int x = 0; x < n; ++x){
        if (fabs(a[x] - 3.3) > PRECISION){
            err += 1;
        }
    }

    return err;
}

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