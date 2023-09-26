#include "acc_testsuite.h"

#ifndef T1
//T1:variable implicit data attributes,V:2.7-3.3
int test1(){
    int err = 0;

    // create a parallel region with a reduction clause
    #pragma acc parallel reduction(+:sum)
    {
        // create a loop with a reduction clause
        #pragma acc loop reduction(+:sum)
        for (int i = 0; i < 10; i++) {
            // access the variable "sum" in the reduction clause
            sum += i;
        }
    }

    // check that the variable "sum" is implicitly private
    #pragma acc parallel
    {
        // access the variable "sum" in the parallel region
        int sum_private = sum;
        // check that the value of "sum_private" is the same as the original "sum"
        if (sum_private != sum) {
            err++;
        }
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