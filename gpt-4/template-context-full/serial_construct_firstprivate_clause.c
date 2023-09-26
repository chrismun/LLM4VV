#include "acc_testsuite.h"

int test_firstprivate(){
    int err = 0;
    int a = 5;
    int a_host = a; 

    #pragma acc serial firstprivate(a) 
    {
        a += 5;
    }

    /* Check if value of a is different on host and device */
    if (a != (a_host + 5)){
        err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    
    /* Run the test NUM_TEST_CALLS times */
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test_firstprivate();
    }
    
    /* Check if any of the runs failed */
    if (failed != 0){
        failcode = (1 << 0);
    }

    return failcode;
}