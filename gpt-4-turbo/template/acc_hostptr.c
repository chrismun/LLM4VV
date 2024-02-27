#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:runtime,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int *a = (int*)malloc(sizeof(int) * size);
    int *hostptr_a;

    // Initializing array on host
    for (int i = 0; i < size; i++) {
        a[i] = rand() % 100;
    }

    #pragma acc enter data copyin(a[0:size])
    hostptr_a = (int *)acc_hostptr(a);

    // Verify acc_hostptr gives access to the original array on the host
    for(int i = 0; i < size; i++) {
        if (hostptr_a[i] != a[i]) {
            err++;
        }
    }

    //Perform operations using acc hostptr on the device
    #pragma acc parallel loop present(a[0:size])
    for (int i = 0; i < size; i++) {
        a[i] += 1;
    }

    // Update host data and verify
    #pragma acc update self(a[0:size])
    for (int i = 0; i < size; i++) {
        if (a[i] != hostptr_a[i] + 1) {
            err++;
        }
    }

    #pragma acc exit data delete(a[0:size])

    free(a);
    return err;
}
#endif

int main(){
    int failcode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed += test1();
    }
    if (failed != 0){
        failcode += (1 << 0);
    }
#endif
    return failcode;
}