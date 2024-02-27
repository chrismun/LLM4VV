#include "acc_testsuite.h"
#ifndef T1
//T1:parallel construct async clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1000;
    int a[size], b[size];
    int i;
    
    // Initialize arrays
    for(i = 0; i < size; ++i){
        a[i] = i;
        b[i] = -i;
    }

    // Launch the first parallel async operation
    #pragma acc parallel loop async(1) copy(a[0:size])
    for(i = 0; i < size; ++i){
        a[i] += 1;
    }
    
    // Launch the second parallel async operation
    #pragma acc parallel loop async(2) copy(b[0:size])
    for(i = 0; i < size; ++i){
        b[i] += 2;
    }
    
    // Wait for all async operations to complete
    #pragma acc wait(1)
    #pragma acc wait(2)

    // Check the results
    for(i = 0; i < size; ++i){
        if(a[i] != i + 1) err += 1; // Error if the value is not correctly incremented
        if(b[i] != -i + 2) err += 1; // Error if the value is not correctly incremented
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