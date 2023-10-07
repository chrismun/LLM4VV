#include "acc_testsuite.h"
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
int test1() {
    const int count = 3;
    int async_ids[count];
    int reductionResult = 0;

    #pragma acc parallel async(async_ids[0])
    {
        #pragma acc loop reduction(+:reductionResult)
        for(int i=0; i<100; i++) {
            reductionResult += i;
        }
    }

    #pragma acc parallel async(async_ids[1])
    {
        #pragma acc loop reduction(+:reductionResult)
        for(int i=0; i<100; i++) {
            reductionResult += i;
        }
    }

    #pragma acc parallel async(async_ids[2])
    {
        #pragma acc loop reduction(+:reductionResult)
        for(int i=0; i<100; i++) {
            reductionResult += i;
        }
    }

    // We expect acc_wait_any to return 0, 1 or 2, otherwise there is a problem
    int return_value = acc_wait_any(count, async_ids);
    if(return_value < 0 || return_value >= count){
        return 1;
    }
    else {
        return 0; // The acc_wait_any call is working properly
    }
}
#endif

int main() {
    const size_t NUM_TEST_CALLS = 5;
    int failed = 0;
    
    #ifndef T1
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = test1();
        if(failed != 0)
            return failed; // If the test fails, stop further tests
    }
    #endif
    
    return 0; // Tests ran successfully
}