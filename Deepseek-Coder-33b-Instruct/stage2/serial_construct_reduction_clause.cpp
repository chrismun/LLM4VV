#include "acc_testsuite.h"
#ifndef T1
//T1:serial construct reduction clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int data[SIZE];
    int sum = 0;

    // Initialize the array with random values
    for(int i = 0; i < SIZE; i++) {
        data[i] = rand() % 100;
    }

    // Compute the sum of the array elements
    #pragma acc serial loop reduction(+:sum)
    for(int i = 0; i < SIZE; i++) {
        sum += data[i];
    }

    if (sum != expected_sum) {
        err++;
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