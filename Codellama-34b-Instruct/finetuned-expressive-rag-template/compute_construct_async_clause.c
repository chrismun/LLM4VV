#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:compute construct async clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int *a, *b, *c, *d, *e, *f;
    int async1 = 1;
    int async2 = 2;
    int async3 = 3;
    int async4 = 4;
    int async5 = 5;
    int async6 = 6;

    a = (int *)malloc(n * sizeof(int));
    b = (int *)malloc(n * sizeof(int));
    c = (int *)malloc(n * sizeof(int));
    d = (int *)malloc(n * sizeof(int));
    e = (int *)malloc(n * sizeof(int));
    f = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = rand() % n;
        b[x] = rand() % n;
        c[x] = 0;
        d[x] = rand() % n;
        e[x] = rand() % n;
        f[x] = 0;
    }

    #pragma acc data copyin(a[0:n], b[0:n], d[0:n], e[0:n]) copy(c[0:n], f[0:n])
    {
        #pragma acc parallel async(async1)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
        #pragma acc parallel async(async2)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                f[x] = d[x] + e[x];
            }
        }
        #pragma acc wait(async1)
        #pragma acc wait(async2)
    }

    for (int x = 0; x < n; ++x){
        if (c[x] != a[x] + b[x] || f[x] != d[x] + e[x]){
            err = 1;
        }
    }

    free(a);
    free(b);
    free(c);
    free(d);
    free(e);
    free(f);

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