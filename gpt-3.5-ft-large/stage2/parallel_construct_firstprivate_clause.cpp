#include "acc_testsuite.h"
#ifndef T1
//T1:parallel construct firstprivate clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    real_t total = 5;

    #pragma acc data copy(total)
    {
        #pragma acc parallel firstprivate(total)
        {
	    #pragma acc loop
            for (int x = 0; x < 10; ++x){
                total = (total / 2.0) + total;
            }
        }
    }

    if (fabs(total - PREU) > PREU){
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