#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef SEED
#define SEED 12345
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// T1:cache directive,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    const int size = 10000;
    double *array = (double*)malloc(size * sizeof(double));

    // Initialize array
    for(int i = 0; i < size; ++i){
        array[i] = (double)rand()/(double)(RAND_MAX);
    }

    double sum_before = 0.0, sum_after = 0.0;

    // Compute sum of a portion of the array without caching
    #pragma acc parallel loop reduction(+:sum_before)
    for(int i = 1000; i < 2000; ++i){
        sum_before += array[i];
    }

    // Compute sum of the same portion but with caching
    #pragma acc parallel loop reduction(+:sum_after)
    #pragma acc cache(array[1000:1000])
    for(int i = 1000; i < 2000; ++i){
        sum_after += array[i];
    }

    // Check if results are the same (they should be)
    if (sum_before != sum_after){
        err = 1;
    }

    free(array);
    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
#ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        if (test1() != 0){
            failed = 1;
            break;
        }
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    if(failcode == 0) {
        printf("Test passed.\n");
    } else {
        printf("Test failed.\n");
    }
    return failcode;
}