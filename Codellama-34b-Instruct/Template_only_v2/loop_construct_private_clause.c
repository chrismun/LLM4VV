#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc parallel loop private(i)
    for (int i = 0; i < 10; i++) {
        int private_var = i;
        #pragma acc loop private(private_var)
        for (int j = 0; j < 10; j++) {
            private_var = j;
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