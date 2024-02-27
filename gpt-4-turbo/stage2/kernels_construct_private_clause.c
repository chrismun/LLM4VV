#include <stdio.h>
#include <stdlib.h>
#include <openacc.h> // Ensure you have the OpenACC library available

#ifndef T1
// T1:kernels construct private clause,V:2.7-3.3

#define SEED 123
#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    srand(SEED);
    const int size = 100;
    int data[size];

    // Initialize data
    for(int i = 0; i < size; ++i){
        data[i] = i;
    }

    // Target kernels construct with private clause
    #pragma acc kernels private(data)
    for(int i = 0; i < size; ++i){
        // This modification should not affect the original data array outside the kernels
        data[i] = rand() % 100;
    }

    // Verify that the original data array outside the kernels is unchanged
    for(int i = 0; i < size; ++i){
        if(data[i] != i){ // Since original data[i] = i
            err++;
        }
    }
    
    return err;
}
#endif

int main(){
    int failcode = 0;

#ifndef T1
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}