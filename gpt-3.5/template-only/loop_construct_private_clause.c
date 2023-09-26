#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Testing OpenACC loop construct with private clause
    int a = 0;
    #pragma acc parallel loop private(a)
    for (int i = 0; i < N; i++) {
        a += 2;
    }

    // Check if the private variable 'a' is correctly incremented
    if (a != 2 * N) {
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