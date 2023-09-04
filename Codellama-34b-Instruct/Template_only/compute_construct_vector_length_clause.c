#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Initialize data
    int data[100];
    for (int i = 0; i < 100; i++) {
        data[i] = i;
    }

    // Set the vector length to 10
    int vector_length = 10;

    // Create a parallel region with the vector length set to 10
    #pragma acc parallel num_gangs(1) vector_length(vector_length)
    {
        // Loop over the data and perform a reduction
        #pragma acc loop reduction(+:data[:10])
        for (int i = 0; i < 100; i++) {
            data[i] += data[i];
        }
    }

    // Check the results
    for (int i = 0; i < 100; i++) {
        if (data[i] != i * 2) {
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