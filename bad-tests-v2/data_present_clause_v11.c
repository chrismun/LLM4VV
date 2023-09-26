#include "acc_testsuite.h"

#ifndef T1
// T1:runtime,data,executable-data,construct-independent,V:2.0-2.7
int test1(){
    int err = 0;
    srand(SEED);

    int data[10];

    // Allocating and initializing data on the device using the present clause
    #pragma acc data present(data)
    {
        #pragma acc enter data copyin(data)

        // Use the data on the device
        #pragma acc parallel loop
        for (int i = 0; i < 10; i++) {
            data[i] = i;
        }
    } // Exit data region, automatic detach and delete actions are performed

    // Verify if the data was correctly modified on the device
    for (int i = 0; i < 10; i++) {
        if (data[i] != i) {
            err = 1;
            break;
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