#include <cstdlib>
#include <iostream>

// Assuming acc_testsuite.h provides necessary setup for testing, including SEED and NUM_TEST_CALLS.
#include "acc_testsuite.h"

#ifndef T1
//T1:parallel,construct,default,clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 100;
    int *a = new int[size];
    int *b = new int[size];
    for(int i = 0; i < size; ++i){
        a[i] = rand() % 100; // Populate with random numbers
        b[i] = 0;
    }
    
    #pragma acc parallel num_gangs(1) vector_length(1) default(none) copyin(a[0:size]) copyout(b[0:size])
    {
        #pragma acc loop
        for(int i = 0; i < size; ++i){
            b[i] = a[i] + 1; // Simple computation to check
        }
    }

    // Verify the computation
    for(int i = 0; i < size; ++i){
        if(b[i] != a[i] + 1){
            err++;
        }
    }

    delete[] a;
    delete[] b;
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
        failcode = failcode + (1 << 0); // Adjusting failcode based on failed tests
    }
#endif
    return failcode;
}