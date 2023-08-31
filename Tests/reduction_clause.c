#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize the input data
    int a[N];
    for (int i = 0; i < N; i++) {
        a[i] = rand() % 100;
    }

    // Initialize the output data
    int b[N];
    for (int i = 0; i < N; i++) {
        b[i] = 0;
    }

    // Reduce the input data using the OpenACC reduction clause
    #pragma acc parallel loop reduction(+:b[i])
    for (int i = 0; i < N; i++) {
        b[i] += a[i];
    }

    // Verify that the reduction result is correct
    for (int i = 0; i < N; i++) {
        if (b[i] != (a[i] + a[i+1] + ... + a[N-1])) {
            err = 1;
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