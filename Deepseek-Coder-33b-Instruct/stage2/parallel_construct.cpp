#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "acc_testsuite.h"

#ifndef T1
//T1:parallel construct,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int N = 1000000;
    int *data = new int[N];
    long long sum = 0;
    long long parallel_sum = 0;

    // Initialize the array with random numbers
    for (int i = 0; i < N; i++) {
        data[i] = rand() % 100;
        sum += data[i];
    }

    // Use the parallel construct to sum the array
#pragma acc parallel loop reduction(+:parallel_sum)
    for (int i = 0; i < N; i++) {
        parallel_sum += data[i];
    }

    // Check if the sums are the same
    if (sum != parallel_sum) {
        err++;
    }

    delete[] data;

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