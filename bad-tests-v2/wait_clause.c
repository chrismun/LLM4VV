#include "acc_testsuite.h"
#ifndef T1
//T1:wait clause,V:2.7-3.3
int test1(){
    int err = 0;
    int *a, *b, *c, *d, *e;
    int n = 1024;
    a = (int *)malloc(n * sizeof(int));
    b = (int *)malloc(n * sizeof(int));
    c = (int *)malloc(n * sizeof(int));
    d = (int *)malloc(n * sizeof(int));
    e = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = 1;
        b[x] = 2;
        c[x] = 3;
        d[x] = 4;
        e[x] = 5;
    }

    #pragma acc data copy(a[0:n], b[0:n], c[0:n], d[0:n], e[0:n])
    {
        #pragma acc parallel present(a[0:n], b[0:n])
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                a[x] += b[x];
            }
        }

        #pragma acc kernels present(c[0:n], d[0:n]) wait(1)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] += d[x];
            }
        }

        #pragma acc serial present(e[0:n]) wait(1)
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                e[x] += 1;
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (a[x] != 3 || c[x] != 9 || e[x] != 6){
            err = 1;
            break;
        }
    }

    free(a);
    free(b);
    free(c);
    free(d);
    free(e);

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