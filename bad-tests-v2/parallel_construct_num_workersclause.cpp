#include "acc_testsuite.h"
#include <openacc.h>

// Testing the parallel construct num_workersclause
int testNumWorkers(){
    int err = 0;
    int total = 100;

    // defining an array to be computed in parallel
    int a[total];

    // initializing data
    for(int i=0; i<total; i++)
        a[i] = i;

    #pragma acc parallel num_workers(4) copy(a)
    {
        #pragma acc loop
        for(int i=0; i<total; i++)
            a[i]*= 2;
    }

    // validation check
    for(int i=0; i<total; i++)
        if (a[i] != i*2)
            err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + testNumWorkers();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    return failcode;
}