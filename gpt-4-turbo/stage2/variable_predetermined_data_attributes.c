#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define SEED 12345
#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    int N = 1024;
    int a[N];

    srand(SEED);
    int reference[N];
    for (int i = 0; i < N; ++i){
        reference[i] = i * 2;  // Expected result for each element
    }

    // Parallel region with loop
    // Each iteration of the loop is supposed to be independent due to the private loop variable
#pragma acc parallel loop
    for (int i = 0; i < N; ++i){
        a[i] = i * 2;
    }

    // Verifying the results
    for (int i = 0; i < N; ++i){
        if (a[i] != reference[i]){
            err++;
        }
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
  
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }

    if (failcode == 0) {
        printf("Test passed.\n");
    } else {
        printf("Test failed.\n");
    }

    return failcode;
}