#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <acc_testsuite.h>

#define NUM_TEST_CALLS 10
#define SEED 12345

int test1(){
    int err = 0;
    srand(SEED);

    // Create a serial construct
    #pragma acc serial
    {
        // Do some work here
        int i = 0;
        for (i = 0; i < 10; i++) {
            printf("Hello from thread %d\n", i);
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    // Run the test 10 times
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}