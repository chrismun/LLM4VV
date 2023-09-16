#include "acc_testsuite.h"
#include <stdio.h>
#include <stdlib.h>

#ifndef T1
//T1:loop construct device_type clause,V:2.7-3.3
int test1(){
    int err = 0;
    int i;
    int *a, *b, *c;

    a = (int *)malloc(N * sizeof(int));
    b = (int *)malloc(N * sizeof(int));
    c = (int *)malloc(N * sizeof(int));

    if (a == NULL || b == NULL || c == NULL) {
        err = 1;
        printf("Error: Memory allocation failed.\n");
        return err;
    }

    // Initialize arrays
    for (i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i + 1;
        c[i] = 0;
    }

    #pragma acc kernels loop device_type(nvidia)
    for (i = 0; i < N; i++) {
        c[i] = a[i] + b[i];
    }

    // Verify the result
    for (i = 0; i < N; i++) {
        if (c[i] != a[i] + b[i]) {
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
        failed += test1();
    }
    if (failed != 0){
        failcode |= (1 << 0);
    }
#endif

    return failcode;
}