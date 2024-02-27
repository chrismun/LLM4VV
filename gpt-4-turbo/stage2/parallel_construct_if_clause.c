#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#ifndef T1
// T1:parallel, construct, if clause, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    bool run_in_parallel = true;
    int a[1024];
    int sequential_sum = 0, parallel_sum = 0;

    // Initialize array
    for (int i = 0; i < 1024; ++i) {
        a[i] = rand() % 10;
        sequential_sum += a[i]; // Calculate sum for verification
    }

    // Attempt to run in parallel depending on the 'run_in_parallel' variable
    #pragma acc parallel loop if(run_in_parallel)
    for (int i = 0; i < 1024; ++i) {
        #pragma acc atomic
        parallel_sum += a[i];
    }

    // Compare the sequential and parallel results
    if (sequential_sum != parallel_sum) {
        err++;
        printf("Test failed: Parallel and sequential sums do not match. Expected %d, got %d.\n", sequential_sum, parallel_sum);
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
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif

    if (failcode == 0) {
        printf("All tests passed successfully.\n");
    } else {
        printf("Some tests failed. Failcode: %d\n", failcode);
    }

    return failcode;
}