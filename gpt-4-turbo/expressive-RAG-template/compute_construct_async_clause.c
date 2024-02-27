#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

//T1:compute construct async clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int *a = (int*)malloc(size * sizeof(int));
    int *b = (int*)malloc(size * sizeof(int));

    // Initialize array `a` on the host
    for(int i = 0; i < size; ++i){
        a[i] = rand() % 100; // random values between 0 and 99
    }

    // Perform an asynchronous computation on `a` to produce `b`
#pragma acc parallel loop copy(a[0:size]) copyout(b[0:size]) async
    for(int i = 0; i < size; ++i){
        b[i] = a[i] + 1; // Simple operation for test
    }

    // Wait for the asynchronous operation to complete
#pragma acc wait

    // Verify the operation was completed correctly
    for(int i = 0; i < size; ++i){
        if(b[i] != a[i] + 1){
            err++;
            break;
        }
    }

    free(a);
    free(b);

    return err;
}

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