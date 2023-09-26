#include <stdio.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
// Test 1: Check if OpenACC computes the if clause correctly
int test1() {
    int err = 0;
    int n = 1000;
    int *a = (int*) malloc(sizeof(int) * n);
    srand(SEED);

    #pragma acc parallel loop if(n > 500)
    for (int i = 0; i < n; ++i) {
        a[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
        if(a[i] != 0) {
            err = 1;
            break;
        }
    }
    
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
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}