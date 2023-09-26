#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define SIZE 1000
#define SEED 1234
#define NUM_TEST_CALLS 100

int test_atomic() {
    int err = 0;
    int* count = (int*) malloc(SIZE * sizeof(int));

    srand(SEED);
    for (int i = 0; i < SIZE; ++i){
        count[i] = 0;
    }

    #pragma acc parallel num_gangs(10) vector_length(32)
    {
        #pragma acc loop gang
        for(int i = 0; i < SIZE; ++i) {
            #pragma acc loop vector
            for(int j = 0; j < SIZE; ++j){
                #pragma acc atomic update
                count[i]++;
            }
        }
    }

    for(int i = 0; i < SIZE; ++i){
        if(count[i] != SIZE){
            err = 1;
        }
    }

    free(count);
    return err;
}

int main(){
    int failcode = 0;
    int failed;
    
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_atomic();
    }
    if (failed != 0){
        failcode = failcode + 1;
        printf("Test failed.\n");
    } else {
        printf("Test passed.\n");
    }
    return failcode;
}