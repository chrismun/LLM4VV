// Test OpenACC acc_attach and acc_detach.
#include "acc_testsuite.h"
#include <stdlib.h>

#ifndef T1
/*T1:acc_attach,acc_detach,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    double *host_data = (double*) malloc(100 * sizeof(double));
    double *dev_data;

    // create data on device and attach to host pointer
    #pragma acc data create(dev_data[0:100])
    {
        acc_attach((void**) &host_data);
        // adding data to verify acc_attach works correctly
        #pragma acc parallel loop present(dev_data[0:100])
        for(int i = 0; i < 100; i++) { 
            dev_data[i] = host_data[i];
        }
        acc_detach((void**) &host_data);
    }    

    // Verifying that host and device data arrays match
    for(int i = 0; i < 100; i++) {
        if(host_data[i] != dev_data[i]) {
            err = 1;
        }
    }

    free(host_data);
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