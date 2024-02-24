#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:compute construct private clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int n = 100;
    int *data = (int*)malloc(n * sizeof(int));
    int sum = 0;

    // Initialize data
    for (int i = 0; i < n; i++) {
        data[i] = rand() % 100;
    }

    // Compute sum in parallel
    #pragma acc parallel private(sum)
    {
        sum = 0;
        #pragma acc loop
        for (int i = 0; i < n; i++) {
            sum += data[i];
        }
    }

    // Check that sum is correct
    int expected_sum = 0;
    for (int i = 0; i < n; i++) {
        expected_sum += data[i];
    }

    if (sum != expected_sum) {
        err = 1;
    }

    free(data);

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