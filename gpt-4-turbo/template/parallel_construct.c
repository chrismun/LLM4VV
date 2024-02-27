#include "acc_testsuite.h"
#ifndef T1
//T1:parallel,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    int n = 1000; // Size of the array
    int a[n], b[n], c[n];
    
    // Initialize arrays
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 100; // Random values between 0 to 99
        b[i] = rand() % 100; // Random values between 0 to 99
        c[i] = 0; // Initialize c array to zero
    }
    
    // Parallel region to add arrays a and b into c
    #pragma acc parallel loop
    for (int i=0; i < n; i++) {
        c[i] = a[i] + b[i];
    }

    // Check results
    for (int i=0; i < n; i++) {
        if(c[i] != a[i] + b[i]){
            err++;
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