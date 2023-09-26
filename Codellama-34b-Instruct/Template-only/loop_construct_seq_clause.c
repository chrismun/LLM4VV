#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a random number between 1 and 10
    int num = rand() % 10 + 1;

    // Create a loop that iterates over the range [1, num]
    for (int i = 1; i <= num; i++) {
        // Do some work
        printf("Iteration %d\n", i);
    }

    // Check if the loop executed correctly
    if (num != i) {
        err = 1;
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