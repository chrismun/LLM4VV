#include <stdio.h>
#include <stdlib.h>
#include <openacc.h>
#include "acc_testsuite.h"

#ifndef T1
//T1:async clause,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int *a, *b, *c, *d, *e, *f;
    int async_arg = acc_async_sync;
    int async_arg_noval = acc_async_noval;
    int async_arg_val = rand() % 256;

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
        d[x] = 0;
        e[x] = 0;
        f[x] = 0;
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(c[0:n]) async(async_arg)
    {
        #pragma acc parallel present(a[0:n], b[0:n], c[0:n]) async(async_arg)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(d[0:n]) async(async_arg_noval)
    {
        #pragma acc parallel present(a[0:n], b[0:n], d[0:n]) async(async_arg_noval)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                d[x] = a[x] - b[x];
            }
        }
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(e[0:n]) async(async_arg_val)
    {
        #pragma acc parallel present(a[0:n], b[0:n], e[0:n]) async(async_arg_val)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                e[x] = a[x] * b[x];
            }
        }
    }

    #pragma acc data copyin(a[0:n], b[0:n]) copyout(f[0:n])
    {
        #pragma acc parallel present(a[0:n], b[0:n], f[0:n]) async(async_arg)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                f[x] = a[x] / b[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (c[x] != (a[x] + b[x])){
            err += 1;
        }
        if (d[x] != (a[x] - b[x])){
            err += 1;
        }
        if (e[x] != (a[x] * b[x])){
            err += 1;
        }
        if (f[x] != (a[x] / b[x])){
            err += 1;
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