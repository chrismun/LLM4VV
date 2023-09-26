#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct gang clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    if (acc_get_device_type() == acc_device_none) {
        return err;
    }
    real_t multipliers[10];
    real_t weights[10];
    real_t computed_weights[10];

    for (int x = 0; x < 10; ++x){
        multipliers[x] = 0.1 * (real_t) rand() / (real_t) (RAND_MAX);
        weights[x] = 100 * multipliers[x];
        computed_weights[x] = 0;
    }

    #pragma acc declare copyin(multipliers[0:10]) copyout(computed_weights[0:10])
    #pragma acc kernels
    {
        #pragma acc loop gang
        for (int x = 0; x < 10; ++x){
            computed_weights[x] = multipliers[x] * weights[x];
        }
    }

    for (int x = 0; x < 10; ++x){
        if (fabs(computed_weights[x] - (0.01 * multipliers[x] * weights[x])) > PRECISION){
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