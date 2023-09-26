#include "acc_testsuite.h"
#ifndef T1
//T1:host_data construct if clause,V:2.7-3.3
int test1(){
    int err = 0;
    int *a, *b, *c, *d, *e, *f;
    int if_clause_result = 0;

    a = (int *)malloc(n * sizeof(int));
    b = (int *)malloc(n * sizeof(int));
    c = (int *)malloc(n * sizeof(int));
    d = (int *)malloc(n * sizeof(int));
    e = (int *)malloc(n * sizeof(int));
    f = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = x;
        b[x] = 0;
        c[x] = 0;
        d[x] = 0;
        e[x] = 0;
        f[x] = 0;
    }

    #pragma acc host_data use_device(a, b, c, d, e, f) if(if_clause_result)
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                b[x] = a[x] + 1;
            }
        }

        #pragma acc kernels
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = b[x] + 1;
            }
        }

        #pragma acc serial
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                d[x] = c[x] + 1;
            }
        }

        #pragma acc parallel loop
        for (int x = 0; x < n; ++x){
            e[x] = d[x] + 1;
        }

        #pragma acc kernels loop
        for (int x = 0; x < n; ++x){
            f[x] = e[x] + 1;
        }
    }

    for (int x = 0; x < n; ++x){
        if (if_clause_result){
            if (a[x] != x || b[x] != x + 1 || c[x] != x + 2 || d[x] != x + 3 || e[x] != x + 4 || f[x] != x + 5){
                err = 1;
            }
        } else {
            if (a[x] != x || b[x] != 0 || c[x] != 0 || d[x] != 0 || e[x] != 0 || f[x] != 0){
                err = 1;
            }
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