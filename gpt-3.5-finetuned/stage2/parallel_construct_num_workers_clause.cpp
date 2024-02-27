#include "acc_testsuite.h"
#ifndef T1
//T1:parallel construct num_workers clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t * a = new real_t[1000];
    real_t * b = new real_t[1000];

    for (int x = 0; x < 1000; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = 0;
    }

    #pragma acc parallel num_workers(128)
    {
        #pragma acc loop
        for (int x = 0; x < 1000; ++x){
            b[x] = a[x];
        }
    }

    for (int x = 0; x < 1000; ++x){
        if (fabs(a[x] - b[x]) > PRECISION){
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