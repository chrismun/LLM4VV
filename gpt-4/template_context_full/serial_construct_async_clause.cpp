#include "acc_testsuite.h"
#include <math.h>

const int THREADS = 1024;
const int BLOCKS = 256;
const int ARRAY_SIZE = THREADS*BLOCKS;
const int FACTORIAL_OF = 5; // Factorial of n, adjust for your testing

float factorial_device[ARRAY_SIZE];

#pragma acc routine seq
float factorial(int n) {
    if(n == 0)
        return 1;
    else
        return n * factorial(n-1);
}

/*T1:serial construct async clause,cond:Variable Factorial */
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc serial async
      factorial_device[0] = factorial(FACTORIAL_OF);

    acc_wait_async();

    // comparing with CPU result
    if(fabs(factorial_device[0] - factorial(FACTORIAL_OF)) > PRECISION){
        err = 1;
    }

    return err;
}

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