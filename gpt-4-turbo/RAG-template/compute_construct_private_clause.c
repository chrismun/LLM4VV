#include "acc_testsuite.h"

#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int N = 1000; // number of iterations, adjust as necessary
    int *a = (int *)malloc(N * sizeof(int));
    int host_a = 0;

    // Initialize array with zeros
    for (int i = 0; i < N; ++i) {
        a[i] = 0;
    }

    #pragma acc parallel num_gangs(10) vector_length(1) private(host_a)
    {
        // Assuming each gang executes this, each should have its own `host_a`
        host_a = 1; // Modify the private copy
        #pragma acc loop
        for (int i = 0; i < N; ++i) {
            a[i] += host_a; // Each gang contributes to adding to 'a'
        }
    }

    // Validate the results
    for (int i = 0; i < N; ++i) {
        if (a[i] != 10) { // Assuming 10 gangs from num_gangs(10)
            err += 1;
        }
    }

    free(a);
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