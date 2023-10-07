#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct tile clause,V:2.7-3.3
int test1(){
    int err = 0;
    int data[N];
    int results[N];
    int host_results[N];
    srand(SEED);

    // Initialize the input data
    for (int i = 0; i < N; i++) {
        data[i] = rand() % 100;
    }

    // Compute the expected results
    for (int i = 0; i < N; i+=2) {
        host_results[i] = data[i] + data[i+1];
        host_results[i+1] = data[i] * data[i+1];
    }

    // Execute the OpenACC kernel with the loop construct tile clause
    #pragma acc data copyin(data[0:N]) copyout(results[0:N])
    #pragma acc parallel loop tile(2)
    for (int i = 0; i < N; i+=2) {
        results[i] = data[i] + data[i+1];
        results[i+1] = data[i] * data[i+1];
    }

    // Verify the results
    for (int i = 0; i < N; i++) {
        if (results[i] != host_results[i]) {
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