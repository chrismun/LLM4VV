#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef SEED
#define SEED 1234
#endif

#ifndef NUM_TEST_CALLS
#define NUM_TEST_CALLS 10
#endif

// T1: atomic construct, V:2.7-3.3
int test_atomic_update(){
    int err = 0;
    int count = 0;
    const int increments = 1000; // Number of increments per thread

    srand(SEED);
    
    #pragma acc parallel num_gangs(1) vector_length(1000)
    {
        #pragma acc loop
        for(int i = 0; i < increments; ++i) {
            #pragma acc atomic update
            count++;
        }
    }

    // After all threads have incremented 'count', its value should be 'increments'
    if (count != increments) {
        fprintf(stderr, "Expected count to be %d but got %d\n", increments, count);
        err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_atomic_update();
    }
    
    if (failed != 0){
        failcode += (1 << 0);
    }
    
    if (failcode == 0) {
        printf("PASS: Atomic update test passed.\n");
    } else {
        printf("FAIL: Atomic update test failed.\n");
    }

    return failcode;
}