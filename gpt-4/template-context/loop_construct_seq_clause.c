#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct seq clause,V:2.7-3.3
int test1(){
    int err = 0; // To store error count
    int a[SIZE], b[SIZE];
    
    srand(SEED);

    // Initiate arrays
    for(int i = 0; i < SIZE; i++){
        a[i] = rand() % SIZE;
        b[i] = a[i];
    }

    // Accelerated seq clause loop
    #pragma acc parallel loop seq
    for(int i = 0; i < SIZE; i++){
        a[i] *= 2;
    }
    
    // Original loop
    for(int i = 0; i < SIZE; i++){
        b[i] *= 2;
    }
    
    // Check if results are equal
    for(int i = 0; i < SIZE; i++){
        if(a[i] != b[i]){
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