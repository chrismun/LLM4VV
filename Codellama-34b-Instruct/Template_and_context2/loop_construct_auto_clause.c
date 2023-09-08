#include "acc_testsuite.h"

#ifndef T1
//T1:loop construct auto clause,V:2.7-3.3
int test1(){
    int err = 0;

    // create an array of random numbers
    int arr[100];
    for (int i = 0; i < 100; i++) {
        arr[i] = rand() % 100;
    }

    // create a loop with the auto clause
    #pragma acc loop auto
    for (int i = 0; i < 100; i++) {
        // do some computation on the array
        arr[i] = arr[i] + 1;
    }

    // check that the loop iterations are data-independent
    for (int i = 0; i < 100; i++) {
        if (arr[i] != arr[i] + 1) {
            err++;
        }
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