#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:parallel construct reduction clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int N = 1000000;
    int *a = new int[N];
    int sum = 0;

    // Initialize array
    for(int i = 0; i < N; i++) {
        a[i] = rand() % 100;
    }

    // Perform parallel reduction
    #pragma acc parallel loop reduction(+:sum)
    for(int i = 0; i < N; i++) {
        sum += a[i];
    }

    // Check the result
    int expected_sum = 0;
    for(int i = 0; i < N; i++) {
        expected_sum += a[i];
    }

    if(sum != expected_sum) {
        err = 1;
    }

    delete [] a;

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