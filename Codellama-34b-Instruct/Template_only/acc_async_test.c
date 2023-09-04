#include "acc_testsuite.h"

// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a data array
    int data[100];
    for (int i = 0; i < 100; i++) {
        data[i] = i;
    }

    // Create a copy of the data array
    int data_copy[100];
    for (int i = 0; i < 100; i++) {
        data_copy[i] = data[i];
    }

    // Create an OpenACC region
    #pragma acc region
    {
        // Create a parallel loop
        #pragma acc parallel loop
        for (int i = 0; i < 100; i++) {
            // Perform some computation on the data array
            data[i] = data[i] + 1;
        }
    }

    // Check that the data array has been modified
    for (int i = 0; i < 100; i++) {
        if (data[i] != data_copy[i] + 1) {
            err = 1;
            break;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    // Run the test
    failed = test1();
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }

    return failcode;
}