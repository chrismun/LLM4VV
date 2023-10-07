#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize data
    int data[100];
    for (int i = 0; i < 100; i++) {
        data[i] = rand() % 100;
    }

    // Create a vector of 10 elements
    int vector[10];
    for (int i = 0; i < 10; i++) {
        vector[i] = data[i];
    }

    // Use the vector in a loop
    for (int i = 0; i < 10; i++) {
        // Do something with the vector element
        vector[i] = vector[i] * 2;
    }

    // Check that the vector elements have been updated
    for (int i = 0; i < 10; i++) {
        if (vector[i] != data[i] * 2) {
            err = 1;
            break;
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