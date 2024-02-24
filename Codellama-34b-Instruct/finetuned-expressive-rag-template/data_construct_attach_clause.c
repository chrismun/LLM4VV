#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:data construct attach clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);

    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    int *c = (int *)malloc(n * sizeof(int));

    int *d_a = (int *)acc_malloc(n * sizeof(int));
    int *d_b = (int *)acc_malloc(n * sizeof(int));
    int *d_c = (int *)acc_malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = rand() % n;
        b[x] = rand() % n;
    }

    acc_attach(a, n * sizeof(int));
    acc_attach(b, n * sizeof(int));
    acc_attach(c, n * sizeof(int));

    #pragma acc data attach(a[0:n], b[0:n], c[0:n])
    {
        #pragma acc kernels
        {
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (c[x] != a[x] + b[x]){
            err = 1;
        }
    }

    acc_detach(a);
    acc_detach(b);
    acc_detach(c);

    acc_free(d_a);
    acc_free(d_b);
    acc_free(d_c);

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