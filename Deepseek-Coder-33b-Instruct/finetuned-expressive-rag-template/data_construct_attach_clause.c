#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>

#ifndef T1
//T1:data construct attach clause,V:2.7-3.3
int test1(){
    int err = 0;
    int n = 10;
    int *a = (int*)malloc(n * sizeof(int));
    int *b = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        a[i] = i;
        b[i] = i;
    }

    #pragma acc data copyin(a[0:n]) copy(b[0:n])
    {
        #pragma acc parallel loop
        for (int i = 0; i < n; i++) {
            b[i] += a[i];
        }
    }

    for (int i = 0; i < n; i++) {
        if (b[i] != 2 * i) {
            err = 1;
            break;
        }
    }

    free(a);
    free(b);

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