#include "acc_testsuite.h"
#include <cstdlib>

//Setting values
#define VECTOR_SIZE 10000
#define INIT_VALUE 5
#define MULT_VALUE 10

#ifndef T1
/*
T1: wait clause, V:2.0-2.7
Testing to confirm the successful completion of independent kernel operations.
*/
int test1() {
    int err = 0;
    srand(SEED);

    // Initialize a vector
    int* vec = new int[VECTOR_SIZE];
    for(int i = 0; i < VECTOR_SIZE; ++i) {
        vec[i] = INIT_VALUE;
    }

    // Parallel GPU operations
    #pragma acc parallel loop async(1)
    for(int i = 0; i < VECTOR_SIZE; ++i) {
        vec[i] *= MULT_VALUE;
    }

    #pragma acc parallel loop async(2)
    for(int i = 0; i < VECTOR_SIZE; ++i) {
        vec[i] += MULT_VALUE;
    }

    #pragma acc wait

    // Checks
    for(int i = 0; i < VECTOR_SIZE; ++i) {
        if(vec[i] != ((INIT_VALUE * MULT_VALUE) + MULT_VALUE)) {
            err++;
        }
    }

    delete[] vec;
    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;
    #ifndef T1
        failed = 0;
        for (int x = 0; x < NUM_TEST_CALLS; ++x){
            failed += test1();
        }
        if (failed != 0) {
            failcode = failcode + (1 << 0);
        }
    #endif
    return failcode;
}