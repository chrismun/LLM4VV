#include "acc_testsuite.h"
#ifndef T1
//T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    // Create a kernel that waits for a signal
    #pragma acc parallel num_gangs(1) num_workers(1) if(1)
    {
        #pragma acc loop gang(1) worker(1)
        for (int i = 0; i < 10; i++) {
            #pragma acc wait(1)
        }
    }

    // Create a kernel that sends a signal
    #pragma acc parallel num_gangs(1) num_workers(1) if(1)
    {
        #pragma acc loop gang(1) worker(1)
        for (int i = 0; i < 10; i++) {
            #pragma acc signal(1)
        }
    }

    // Wait for the signal to be sent
    #pragma acc parallel num_gangs(1) num_workers(1) if(1)
    {
        #pragma acc loop gang(1) worker(1)
        for (int i = 0; i < 10; i++) {
            #pragma acc wait(1)
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