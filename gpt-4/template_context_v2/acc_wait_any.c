#include "acc_testsuite.h"
#include <stdlib.h>
#include <time.h>

#ifndef T1
//T1:acc wait any,V:2.7-3.3
int test1(){
    int err = 0;
    int *a, *b, *c;
    int n = 1000;

    a = (int*)malloc(sizeof(int)*n);
    b = (int*)malloc(sizeof(int)*n);
    c = (int*)malloc(sizeof(int)*n);

    // Initialization
    srand(time(0));
    for(int i = 0; i < n; i++) {
        a[i] = rand() % 1000;
        b[i] = rand() % 1000;
        c[i] = 0;
    }

    #pragma acc parallel loop async(1)
    for(int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }

    #pragma acc parallel loop async(2)
    for(int i = 0; i < n; i++) {
        b[i] = a[i] * b[i];
    }

    #pragma acc wait any(1, 2)

    // Verification
    for(int i = 0; i < n; i++) {
        if(c[i]!= a[i]+b[i]) {
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
    return failcode;
}