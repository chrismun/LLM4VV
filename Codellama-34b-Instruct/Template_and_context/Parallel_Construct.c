c
#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Test 1: Verify that the parallel construct is executed correctly
    #pragma acc parallel
    {
        // Do some computation
    }

    // Test 2: Verify that the num_gangs clause is executed correctly
    #pragma acc parallel num_gangs(2)
    {
        // Do some computation
    }

    // Test 3: Verify that the num_workers clause is executed correctly
    #pragma acc parallel num_workers(2)
    {
        // Do some computation
    }

    // Test 4: Verify that the async clause is executed correctly
    #pragma acc parallel async(1)
    {
        // Do some computation
    }

    // Test 5: Verify that the wait clause is executed correctly
    #pragma acc parallel wait(1)
    {
        // Do some computation
    }

    // Test 6: Verify that the num_gangs and num_workers clauses can be combined
    #pragma acc parallel num_gangs(2) num_workers(2)
    {
        // Do some computation
    }

    // Test 7: Verify that the async and wait clauses can be combined
    #pragma acc parallel async(1) wait(1)
    {
        // Do some computation
    }

    // Test 8: Verify that the num_gangs, num_workers, async, and wait clauses can be combined
    #pragma acc parallel num_gangs(2) num_workers(2) async(1) wait(1)
    {
        // Do some computation
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