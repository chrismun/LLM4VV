#include "acc_testsuite.h"

// T1:set directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    // Create a set of data
    int data[10];
    for (int i = 0; i < 10; i++) {
        data[i] = rand();
    }

    // Set the data to a specific value
    int value = 42;
    #pragma acc set(data[0:10]) value(value)

    // Check that the data has been set correctly
    for (int i = 0; i < 10; i++) {
        if (data[i] != value) {
            err = 1;
            break;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    // Run the test multiple times to ensure it passes consistently
    for (int x = 0; x < NUM_TEST_CALLS; x++) {
        failed = test1();
        if (failed != 0) {
            failcode = failcode + (1 << x);
        }
    }

    return failcode;
}