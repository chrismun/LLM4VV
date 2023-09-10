#include "acc_testsuite.h"
#ifndef T1
//T1:parallel construct reduction clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t reduction = 0.0;

    #pragma acc data copy(reduction)
    # {
        #pragma acc parallel reduction(+:reduction)
        # {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                reduction += (5.0 / (n));
            }
        # }
    # }

    real_t prior_val = 0;
    real_t local_temp = 0;
    for (int x = 0; x < n; ++x){
        local_temp = 0;
        for (int y = 0; y < n; ++y){
            local_temp += 5.0/n;
        }
        if (fabs(local_temp - prior_val) > PRECISION){
            err += 1;
        }
        prior_val = local_temp;
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