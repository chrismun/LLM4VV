#include "acc_testsuite.h"
#ifndef T1
/*T1:loop construct reduction clause,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);

    int x = 0;
    const int I = 1000;
    const int J = 1000;
    const int K = 1000;

    #pragma acc parallel copy(x)
    {
        #pragma acc loop gang reduction(+:x)
        for (int i = 0; i < I; ++i) {
            #pragma acc loop worker reduction(+:x)
            for (int j = 0; j < J; ++j) {
                #pragma acc loop vector reduction(+:x)
                for (int k = 0; k < K; ++k) {
                    x += 1;
                }
            }
        }
    }

    if (x != I * J * K){
        err = 1;
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