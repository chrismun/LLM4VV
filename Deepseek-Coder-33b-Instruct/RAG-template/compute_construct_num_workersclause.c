#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:{feature},V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int num_workers = rand() % acc_get_num_devices() + 1; // Generate a random number of workers

    #pragma acc parallel num_workers(num_workers)
    {
        // Do some work here
    }

    // Check if the number of workers is as expected
    if (acc_get_num_workers() != num_workers) {
        err++;
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