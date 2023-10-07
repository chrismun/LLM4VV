#include <stdio.h>
#include <stdlib.h>
#include "acc_testsuite.h"
#ifndef T1
int test1(){
    int N = 1000;
    float err = 0.0;
    float *a, *b, *c;

    a = (float*)malloc(sizeof(float)*N);
    b = (float*)malloc(sizeof(float)*N);
    c = (float*)malloc(sizeof(float)*N);

    for (int i=0; i<N; i++){
        a[i] = (float)rand() / (float)RAND_MAX;
        b[i] = (float)rand() / (float)RAND_MAX;
    }

    #pragma acc parallel loop copyin(a[0:N], b[0:N]) copyout(c[0:N])
    for(int i=0; i<N; i++) {
        c[i] = a[i] + b[i];
    }

    for(int i=0; i<N; i++) {
        if(c[i] != a[i] + b[i]) {
            err = 1;
            break;
        }
    }

    free(a);
    free(b);
    free(c);

    return err;
}
#endif

int main() {
    int failCode = 0;
    int failed;
#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failCode = failCode + (1 << 0);
    }
#endif
    return failCode;
}