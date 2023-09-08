#include "acc_testsuite.h"

#ifndef T1
//T1:serial construct,V:2.7-3.3
int test1(){
    int err = 0;

    // Set up data for the test
    int data[10];
    for (int i = 0; i < 10; i++) {
        data[i] = i;
    }

    // Execute the serial construct
    #pragma acc serial
    {
        // Perform some computation on the data
        for (int i = 0; i < 10; i++) {
            data[i] = data[i] * 2;
        }
    }

    // Check the results
    for (int i = 0; i < 10; i++) {
        if (data[i] != i * 2) {
            err++;
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