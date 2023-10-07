#include "acc_testsuite.h"
#ifndef T1
//T1:compute construct num_workersclause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int num_workers = 7; // Set your desired number of workers
    int n = 200;
    int test[n];
    for(int i = 0; i < n; i++){ 
       test[i] = i;
    }

    #pragma acc data copy(test[0:n])
    {
    #pragma acc parallel loop num_workers(num_workers)
       for(int i = 0; i < n; i++){ 
          test[i] = test[i] + 1; 
       }
    }

    for(int i = 0; i < n; i++){ 
       if(test[i] != i+1){
            err = 1;
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