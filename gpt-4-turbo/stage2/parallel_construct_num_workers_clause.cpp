#include "acc_testsuite.h"
#include <stdlib.h>
#include <openacc.h>
#include <stdio.h>

#ifndef T1
//T1:parallel construct num_workers clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int size = 10000;
    int* a = new int[size];
    int expected_sum = 0;

    // Initialize array with random values and compute their expected sum.
    for (int i = 0; i < size; ++i) {
        a[i] = rand() % 100;
        expected_sum += a[i];
    }

    int actual_sum = 0;
    // Use a parallel region with a specific number of workers
    #pragma acc parallel num_workers(4) copy(a[0:size])
    {
        #pragma acc loop reduction(+:actual_sum)
        for (int i = 0; i < size; ++i) {
            actual_sum += a[i];
        }
    }

    // Check if the actual sum matches the expected sum.
    if (actual_sum != expected_sum) {
        err = 1; // Error if sums don't match
    }

    delete[] a;
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
    printf("Test %s\n", failcode == 0 ? "PASSED" : "FAILED");
    return failcode;
}