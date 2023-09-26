#include "acc_testsuite.h"

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Specify OpenACC directives to test reference counters
    #pragma acc data copyin(x)
    #pragma acc parallel loop
    for (int i = 0; i < N; i++){
        x[i]++;
    }

    // Verify results
    for (int i = 0; i < N; i++){
        if (x[i] != 1){
            err = 1;
            break;
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