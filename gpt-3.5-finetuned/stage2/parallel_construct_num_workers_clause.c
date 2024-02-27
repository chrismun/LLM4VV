#include "acc_testsuite.h"
#ifndef T1
//T1:parallel construct num_workers clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    #pragma acc parallel num_workers(16)
    {
    /* returns the total number of CPUs usable by the program */
    int numCPU = acc_get_num_workers();

    if(numCPU != 16){
        err += 1;
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