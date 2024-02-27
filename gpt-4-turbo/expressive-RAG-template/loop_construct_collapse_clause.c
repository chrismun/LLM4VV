#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// T1: loop construct collapse clause, V: 2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    
    const int dim1 = 10, dim2 = 10;
    int a[dim1][dim2] = {0};

    #pragma acc parallel loop collapse(2)
    for (int i = 0; i < dim1; i++){
        for (int j = 0; j < dim2; j++){
            a[i][j]++;
        }
    }
    
    // Verify that each element has been incremented exactly once.
    for (int i = 0; i < dim1; i++) {
        for (int j = 0; j < dim2; j++) {
            if (a[i][j] != 1) {
                err++;
            }
        }
    }
    
    return err;
}

int main(){
    int failcode = 0;
    int failed;
    
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    
    if (failcode == 0) {
        printf("Test passed.\n");
    } else {
        printf("Test failed.\n");
    }
    
    return failcode;
}