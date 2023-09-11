#include "acc_testsuite.h"

#ifndef T1
//T1:parallel construct,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc parallel
    {
        int i = 0;
        for (i = 0; i < 10; i++) {
            printf("Thread %d: %d\n", i, i);
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