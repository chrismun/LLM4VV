#include "openacc.h"
#include <stdio.h>
#include <stdlib.h>

int test1(){
    int err = 0;

    acc_init(acc_device_default);

    #pragma acc parallel loop
    for(int i = 0; i < 100; i++) {
        printf("Parallel loop iteration: %d\n", i);
    }
    
    acc_shutdown(acc_device_default);

    /* Testing acc_shutdown by trying to re-run loop after shutdown */
        
    #pragma acc parallel loop
    for (int i = 0; i < 100; i++) {
        /* If this point is reached without error, then shutdown was not successful */
        err = 1;
    }

    return err;
}

int main(){
    int failcode = 0;
    int failed = 0;
    
    for (int x = 0; x < 100; ++x) { // replace 100 with your desired NUM_TEST_CALLS
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
    
    return failcode;
}