#include <stdio.h>
#include <stdlib.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:compute construct wait clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int n = 1000;
    int *a = (int*)malloc(n * sizeof(int));
    int *b = (int*)malloc(n * sizeof(int));
    int *c = (int*)malloc(n * sizeof(int));
    int *d = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++){
        a[i] = rand() % 10;
        b[i] = rand() % 10;
        c[i] = 0;
        d[i] = 0;
    }

    #pragma acc kernels
    {
        #pragma acc loop independent
        for (int i = 0; i < n; i++){
            c[i] = a[i] + b[i];
        }
    }
    
    #pragma acc kernels wait
    {
        #pragma acc loop independent
        for (int i = 0; i < n; i++){
            d[i] = a[i] - b[i];
        }
    }

    for (int i = 0; i < n; i++){
        if (c[i] != a[i] + b[i] || d[i] != a[i] - b[i]){
            err = 1;
            break;
        }
    }

    free(a);
    free(b);
    free(c);
    free(d);

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