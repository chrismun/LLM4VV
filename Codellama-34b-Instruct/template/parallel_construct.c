#include "acc_testsuite.h"

#ifndef T1
//T1:parallel construct,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc parallel
    {
        int i = 0;
        #pragma acc loop
        for (i = 0; i < 10; i++) {
            int j = i * 2;
            #pragma acc loop
            for (int k = 0; k < 10; k++) {
                j += k;
            }
        }
    }

    if (j != 100) {
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