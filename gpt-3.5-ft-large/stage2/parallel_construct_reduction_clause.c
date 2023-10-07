#include "acc_testsuite.h"
#ifndef T1
//T1:parallel construct reduction clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    real_t cumulative_reduction = 0.0;
    real_t reduction;

    #pragma acc data copyin(reduction) copy(cumulative_reduction)
    {
        #pragma acc parallel reduction(+:cumulative_reduction)
        {
            for (int x = 0; x < n; ++x){
                #pragma acc loop reduction(+:reduction)
                for (int y = 0; y < m; ++y){
                    reduction += (1 + rand() / (real_t)(RAND_MAX)) / m;
                }
                cumulative_reduction += reduction / n;
                for (int y = 0; y < m; ++y){
                    reduction -= (1 + rand() / (real_t)(RAND_MAX)) / m;
                }
            }
        }
     }

     if (fabs(cumulative_reduction - 1) > PRECISION){
         err += 1;
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