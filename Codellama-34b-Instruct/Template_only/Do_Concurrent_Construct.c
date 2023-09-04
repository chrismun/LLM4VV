#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc parallel
    {
        int i = 0;
        #pragma acc loop
        for (i = 0; i < 10; i++) {
            #pragma acc concurrent
            {
                int j = 0;
                #pragma acc loop
                for (j = 0; j < 10; j++) {
                    if (i == j) {
                        err = 1;
                    }
                }
            }
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