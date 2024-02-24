#include "acc_testsuite.h"
#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // create a data region
    #pragma acc data create(a[0:N])
    {
        // initialize the data region
        for (int i = 0; i < N; i++) {
            a[i] = i;
        }

        // check the data region
        for (int i = 0; i < N; i++) {
            if (a[i] != i) {
                err++;
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