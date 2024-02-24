#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:compute construct num_workersclause,V:2.7-3.3
int test1(){
    int err = 0;
    int n = 1000;
    int *a = (int*)malloc(n * sizeof(int));
    int *b = (int*)malloc(n * sizeof(int));
    int *c = (int*)malloc(n * sizeof(int));

    for(int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = i;
        c[i] = 0;
    }

    #pragma acc parallel loop num_workers(4)
    for(int i = 0; i < n; i++) {
        c[i] = a[i] + b[i];
    }

    for(int i = 0; i < n; i++) {
        if(c[i] != 2*i) {
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
    failed = failed + test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}