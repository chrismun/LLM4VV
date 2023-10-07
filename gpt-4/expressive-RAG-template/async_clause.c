#include "acc_testsuite.h"
#include <stdlib.h>
#include <assert.h>

// T1:async clause,V:2.7-3.3
int test1() {
    int err = 0;
    int size = 4096;
    float* a = (float*) malloc(sizeof(float) * size);
    float* result = (float*) malloc(sizeof(float) * size);

    for(int i = 0; i < size; ++i) {
        a[i] = (float)i;
        result[i] = 0;
    }

    #pragma acc kernels async
    for (int i = 0; i < size; ++i) {
        result[i] += a[i];
    }

    #pragma acc wait

    for(int i = 0; i < size; ++i) {
        if (a[i] != result[i]) {
            err = 1;
            break;
        }
    }

    free(a);
    free(result);

    return err;
}

int main(){
    int failcode = 0;
    int failed;
    failed = 0;
    
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
    
    return failcode;
}