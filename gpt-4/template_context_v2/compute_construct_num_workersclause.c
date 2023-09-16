#include "acc_testsuite.h"
#ifndef T1
//T1:compute construct num_workersclause,V:2.7-3.3
int test_num_workers(){

    int err = 0;
    int num_workers = 4;
    int count = 0;

    #pragma acc parallel num_workers(num_workers)
    {
        #pragma acc loop worker reduction(+:count)
        for(int i = 0; i < num_workers; i++){
           count++;
        }
    }

    if(count != num_workers){
        err = 1; // Error occurs.
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
        failed = failed + test_num_workers();
    }
    if (failed != 0){
        failcode = failcode + 1;
    }
#endif
    return failcode;
}