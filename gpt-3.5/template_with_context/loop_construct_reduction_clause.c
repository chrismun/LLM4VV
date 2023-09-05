#include "acc_testsuite.h"

#ifndef T1
// T1: runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    int x = 0;

    #pragma acc parallel copy(x)
    {
        // gang-shared x undefined
        #pragma acc loop gang reduction(+:x)
        for (int i = 0; i < I; ++i) {
            x += 1; // vector-private x modified
        }// worker-private x updated for vector reduction
    }// gang-shared x updated for gang reduction
    // x = I

    if (x != I) {
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