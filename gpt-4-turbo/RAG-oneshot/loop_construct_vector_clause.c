#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "acc_testsuite.h"

#ifndef T1
// T1:loop,vector,V:1.0-2.7
int test1(){
    int err = 0;
    srand(SEED);
    real_t *a = (real_t *)malloc(n * sizeof(real_t));
    real_t *b = (real_t *)malloc(n * sizeof(real_t));
    real_t *c = (real_t *)malloc(n * sizeof(real_t));

    for (int x = 0; x < n; ++x){
        a[x] = rand() / (real_t)(RAND_MAX / 10);
        b[x] = rand() / (real_t)(RAND_MAX / 10);
        c[x] = 0;
    }

    #pragma acc kernels
    {
        #pragma acc loop vector
        for (int x = 0; x < n; ++x){
            c[x] = a[x] + b[x];
        }
    }

    for (int x = 0; x < n; ++x){
        if (fabs(c[x] - (a[x] + b[x])) > PRECISION){
            err += 1;
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
    failed = test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    if (failcode == 0) {
        printf("PASSED\n");
    } else {
        printf("FAILED\n");
    }
    return failcode;
}