#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#define NUM_TEST_CALLS 1000
#define SEED 123

int test1(){
    int err = 0;
    srand(SEED);

    int x = 0;
    #pragma acc parallel loop gang worker vector
    for (int i = 0; i < NUM_TEST_CALLS; ++i){
        #pragma acc atomic update
        x++;
    }

    if (x != NUM_TEST_CALLS){
        err = 1;
        printf("Error: x = %d, expected %d\n", x, NUM_TEST_CALLS);
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

    return failcode;
}