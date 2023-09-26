#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Set up the loop construct with the collapse clause
    #pragma acc parallel loop collapse(2)
    for (int i = 0; i < 360; i++) {
        for (int j = 0; j < N; j++) {
            // Do something
        }
    }

    // Check if the collapse clause was applied correctly
    if (acc_get_num_gangs(acc_get_device_type()) != 2) {
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