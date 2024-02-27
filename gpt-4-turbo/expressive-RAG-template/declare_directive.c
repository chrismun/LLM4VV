#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#ifndef T1
// T1:declare directive,V:2.7-3.3
int test1(){
    int err = 0;
    const int n = 100;
    int *a = (int*) malloc(n * sizeof(int));
    int *b = (int*) malloc(n * sizeof(int));

    // Initialize array
    for(int i = 0; i < n; ++i){
        a[i] = i;
    }

    // Using OpenACC declare directive to mark 'a' for copyin
    #pragma acc declare copyin(a[0:n])

    // Explicit data region to ensure 'a' is copied in
    #pragma acc data copyout(b[0:n])
    {
        // Parallel region to perform computation
        #pragma acc parallel loop
        for(int i = 0; i < n; ++i){
            b[i] = a[i] + 1; // Simple computation to verify data transfer
        }
    }

    // Checking results
    for(int i = 0; i < n; ++i){
        if(b[i] != i + 1){
            err++;
        }
    }

    free(a);
    free(b);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    const int NUM_TEST_CALLS = 10;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    return failcode;
}