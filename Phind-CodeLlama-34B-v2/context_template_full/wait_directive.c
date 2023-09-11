#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
/*T1:wait directive,V:2.0-2.7*/
int test1(){
    int err = 0;
    srand(SEED);
    int *a, *b, *c, i;
    a = (int *)malloc(n * sizeof(int));
    b = (int *)malloc(n * sizeof(int));
    c = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++) {
        a[i] = rand() % n;
        b[i] = rand() % n;
    }

    #pragma acc data copy(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc parallel loop
        for (i = 0; i < n; i++) {
            c[i] = a[i] + b[i];
        }

        #pragma acc wait

        #pragma acc parallel loop
        for (i = 0; i < n; i++) {
            c[i] = c[i] * 2;
        }
    }

    for (i = 0; i < n; i++) {
        if (c[i] != (a[i] + b[i]) * 2) {
            err = 1;
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