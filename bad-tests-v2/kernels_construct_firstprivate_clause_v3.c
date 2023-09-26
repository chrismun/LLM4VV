#include "acc_testsuite.h"
#ifndef T1
//T1:kernels construct firstprivate clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int firstprivate reduction = 0;

    #pragma acc kernels firstprivate(firstprivate)
    {
        int loop_reduction = 0;
        for (int x = 0; x < n; ++x){
            firstprivate = 1.0;
        }
        for (int x = 0; x < n; ++x){
            loop_reduction += data[x];
        }
        firstprivate = loop_reduction;
        for (int x = 0; x < n; ++x){
            firstprivate[x] -= data[x];
        }
        for (int x = 0; x < n; ++x){
            reduction += data[x];
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
    int x;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}