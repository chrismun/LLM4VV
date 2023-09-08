#include "acc_testsuite.h"

#ifndef T1
//T1:combined constucts,V:2.7-3.3
int test1(){
    int err = 0;

    // Set up the data
    int data[100];
    for (int i = 0; i < 100; i++) {
        data[i] = i;
    }

    // Use a parallel loop to compute the sum of the data
    #pragma acc parallel loop reduction(+:sum)
    for (int i = 0; i < 100; i++) {
        sum += data[i];
    }

    // Use a serial loop to compute the sum of the data
    #pragma acc serial loop reduction(+:sum)
    for (int i = 0; i < 100; i++) {
        sum += data[i];
    }

    // Use a kernels loop to compute the sum of the data
    #pragma acc kernels loop reduction(+:sum)
    for (int i = 0; i < 100; i++) {
        sum += data[i];
    }

    // Check the results
    if (sum != 4950) {
        err = 1;
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