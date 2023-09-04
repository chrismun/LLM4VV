#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Set the default async mode to true
    acc_set_default_async(true);

    // Create a data array
    int data[10];

    // Initialize the data array with random values
    for (int i = 0; i < 10; i++) {
        data[i] = rand();
    }

    // Create a parallel region with the default async mode
    #pragma acc parallel
    {
        // Create a loop to iterate over the data array
        #pragma acc loop
        for (int i = 0; i < 10; i++) {
            // Perform some computation on the data array
            data[i] = data[i] + 1;
        }
    }

    // Check the results of the computation
    for (int i = 0; i < 10; i++) {
        if (data[i] != i + 1) {
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