#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:serial construct wait clause,V:2.7-3.3
int test1(){
    int err = 0;
    int data[100];
    int i;

    // Initialize data
    for (i = 0; i < 100; i++) {
        data[i] = i;
    }

    // Parallel region
    #pragma acc parallel loop
    for (i = 0; i < 100; i++) {
        data[i] *= 2;
    }

    // Wait for all kernels to finish
    #pragma acc wait

    // Check the results
    for (i = 0; i < 100; i++) {
        if (data[i] != i * 2) {
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
    failed = failed + test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}