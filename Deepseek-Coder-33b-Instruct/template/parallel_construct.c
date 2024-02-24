#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int N = 1000000;
    int *data = (int*)malloc(N * sizeof(int));
    int sum = 0;

    // Initialize the array with random numbers
    for(int i = 0; i < N; i++) {
        data[i] = rand() % 100;
    }

    // Use OpenACC to parallelize the summation
    #pragma acc parallel loop reduction(+:sum)
    for(int i = 0; i < N; i++) {
        sum += data[i];
    }

    // Check the result
    int expected_sum = 0;
    for(int i = 0; i < N; i++) {
        expected_sum += data[i];
    }

    if(sum != expected_sum) {
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