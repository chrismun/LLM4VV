pp
#include "acc_testsuite.h"

#ifndef T2
//T2:kernels,data,declare,copy,V:1.0-2.7
real_t a;

int test2(){
    int err = 0;
    srand(SEED);
    real_t prev_a = rand() / (real_t)(RAND_MAX / 10);
    a = prev_a;

    real_t b;

    #pragma acc declare copy(a)

    #pragma acc kernels
    {
        b = a;
    }

    if (fabs(b - prev_a) > PRECISION){
        err += 1;
    }

    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T2
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test2();
    }
    if (failed != 0){
        failcode = failcode + (1 << 1);
    }
#endif

    return failcode;
}