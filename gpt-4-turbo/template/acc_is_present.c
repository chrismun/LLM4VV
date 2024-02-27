#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int a[size];
    int b[size];

    // Initialize arrays
    for(int i = 0; i < size; ++i){
        a[i] = rand() % 100; // Values between 0 and 99
        b[i] = a[i]; // Copying 'a' to 'b' for verification
    }

    // Compute in parallel using OpenACC
#pragma acc parallel loop
    for(int i = 0; i < size; ++i){
        a[i] += 1; // Increment each element
    }

    // Verify the results
    for(int i = 0; i < size; ++i){
        if(a[i] != b[i] + 1){
            err++;
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