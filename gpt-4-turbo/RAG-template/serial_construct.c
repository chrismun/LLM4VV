#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

// Assuming SEED and NUM_TEST_CALLS are defined in "acc_testsuite.h"
// Adjust these values according to your actual test suite's specifications
#define SEED 123
#define NUM_TEST_CALLS 10

#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int n = 1024;
    int a[n], b[n], c[n];
    
    // Initialize arrays
    for(int i = 0; i < n; i++){
        a[i] = rand() % 100;
        b[i] = rand() % 100;
    }

    // Compute vector addition in a serial construct
    #pragma acc data copyin(a[0:n],b[0:n]) copyout(c[0:n])
    {
        #pragma acc serial
        for(int i = 0; i < n; i++){
            c[i] = a[i] + b[i];
        }
    }

    // Validate results
    for(int i = 0; i < n; i++){
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
        printf("Test1 Failed\n");
        failcode = failcode + (1 << 0);
    } else {
        printf("Test1 Passed\n");
    }
#endif

    return failcode;
}