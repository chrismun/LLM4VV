#include <stdio.h>
#include <stdlib.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:data present,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    const int size = 1024;
    int *a, *b, *c;
    a = (int *)malloc(size * sizeof(int));
    b = (int *)malloc(size * sizeof(int));
    c = (int *)malloc(size * sizeof(int));

    // Initialize arrays
    for (int i = 0; i < size; ++i){
        a[i] = rand() % 100;
        b[i] = rand() % 100;
        c[i] = 0;
    }

    // Mark arrays as present on the device
    #pragma acc enter data copyin(a[0:size], b[0:size])

    // Test the data present clause
    #pragma acc parallel loop present(a, b, c)
    for (int i = 0; i < size; ++i) {
        c[i] = a[i] + b[i];
    }

    // Check results
    for (int i = 0; i < size; ++i){
        if(c[i] != a[i] + b[i]){
            err++;
        }
    }

    // Free arrays from device
    #pragma acc exit data delete(a[0:size], b[0:size])

    free(a);
    free(b);
    free(c);

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