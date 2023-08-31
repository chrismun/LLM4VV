#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize the data
    int data[N];
    for (int i = 0; i < N; i++) {
        data[i] = i;
    }

    // Create the OpenACC do construct
    #pragma acc parallel loop gang(static:1) num_gangs(N) vector(128)
    for (int i = 0; i < N; i++) {
        data[i] = data[i] + 1;
    }

    // Check if the data is correct
    for (int i = 0; i < N; i++) {
        if (data[i] != i + 1) {
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