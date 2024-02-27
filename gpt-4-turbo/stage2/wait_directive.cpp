#include <iostream>
#include <stdlib.h>
#include <vector>
#include "acc_testsuite.h"

#ifndef T1
// T1: wait directive, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1000;
    std::vector<int> host_data(size, 0);
    std::vector<int> verify_data(size);
    
    // Initialize verify data on host for later comparison
    for (int i = 0; i < size; ++i) {
        verify_data[i] = i * 2;
    }

    // Perform parallel operations
    #pragma acc parallel loop async(1)
    for(int i = 0; i < size; ++i){
        host_data[i] = i * 2;
    }

    // Wait for the above operations to complete before continuing
    #pragma acc wait(1)

    // Verification
    for(int i = 0; i < size; ++i){
        if (host_data[i] != verify_data[i]) {
            err = 1; // Error if results do not match expected
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
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
    #endif
    return failcode;
}