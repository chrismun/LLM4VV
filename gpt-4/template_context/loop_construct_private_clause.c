#include "acc_testsuite.h"
#include <stdlib.h>
#include <stdio.h>

#ifndef T1
//T1:loop construct private clause,V:2.7-3.3
int test1(){
    int n = 100;
    double *a = (double*)malloc(n*sizeof(double));
    double *b = (double*)malloc(n*sizeof(double));
    double *c = (double*)malloc(n*sizeof(double));

    // Initialize arrays a, b, and c 
    for(int i=0; i<n; i++){
        a[i] = i;
        b[i] = i*2;
        c[i] = i*3;
    }

    #pragma acc parallel
    {
        double tmp;
        #pragma acc loop private(tmp)
        for(int i=0; i<n; i++){
            tmp = b[i] + c[i];
            a[i] = a[i] + tmp;
        }
    }

    int err = 0;
    for(int i=0; i<n; i++){
        if (a[i] != i + (b[i] + c[i])){
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
    printf("Failcode: %d\n", failcode);
    return failcode;
}