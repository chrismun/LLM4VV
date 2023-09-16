#include "acc_testsuite.h"

// T1: compute construct firstprivate clause, V:2.7-3.3
int test1() {
    int err = 0;
    srand(SEED);
    int original = rand() % 100;
    int copy;

    #pragma acc parallel firstprivate(original, copy)
    {
        copy = original;
    }
    // Checking if the copied value inside the parallel region retained its initial value
    if(copy != original){
        err = 1;
    }
    return err;
}

int main(){
    int failcode = 0;
    int failed;
    failed = 0;
    // NUM_TEST_CALLS is a predefined constant. Substitute with your desired number of iterations.
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    // If there is any error, add 1 to the failcode.
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}