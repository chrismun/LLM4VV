#include <stdio.h>
#include <stdlib.h>
#include <openacc.h> // Ensure to include OpenACC library

// Simple definition for seed and number of test calls
#define SEED 12345
#define NUM_TEST_CALLS 10

#ifndef T1
// T1:kernels construct self clause, V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int a[size];

    // Initialize array
    for(int i = 0; i < size; i++) {
        a[i] = i;
    }

    #pragma acc kernels self(a[0:size])
    for(int i = 0; i < size; i++) {
        a[i] += 1;
    }

    // Verification
    for(int i = 0; i < size; i++) {
        if(a[i] != i + 1) {
            err += 1;
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