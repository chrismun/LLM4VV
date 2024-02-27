#include "acc_testsuite.h"
#ifndef T1
//T1:acc delete,V:2.7-3.3
int test1(){
    int err = 0;
    srand(SEED);
    int *a = (int *)malloc(n * sizeof(int));
    int *b = (int *)malloc(n * sizeof(int));
    int *c = (int *)malloc(n * sizeof(int));
    int *d = (int *)malloc(n * sizeof(int));
    int *e = (int *)malloc(n * sizeof(int));
    int *f = (int *)malloc(n * sizeof(int));
    int *g = (int *)malloc(n * sizeof(int));
    int *h = (int *)malloc(n * sizeof(int));
    int *i = (int *)malloc(n * sizeof(int));
    int *j = (int *)malloc(n * sizeof(int));

    for (int x = 0; x < n; ++x){
        a[x] = rand() % 10;
        b[x] = rand() % 10;
        c[x] = 0;
        d[x] = rand() % 10;
        e[x] = rand() % 10;
        f[x] = 0;
        g[x] = rand() % 10;
        h[x] = 0;
        i[x] = rand() % 10;
        j[x] = 0;
    }

    #pragma acc enter data create(c[0:n], f[0:n], h[0:n], j[0:n])
    #pragma acc data copyin(a[0:n], b[0:n], d[0:n], e[0:n], g[0:n]) present(c[0:n], f[0:n], h[0:n], j[0:n])
    {
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                c[x] = a[x] + b[x];
            }
        }
        acc_delete(d, n * sizeof(int));
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x =  0; x < n; ++x){
                f[x] = c[x] + e[x];
            }
        }
        acc_delete(g, n * sizeof(int));
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                h[x] = f[x] + c[x];
            }
        }
        acc_delete(i, n * sizeof(int));
        #pragma acc parallel
        {
            #pragma acc loop
            for (int x = 0; x < n; ++x){
                j[x] = h[x] + c[x];
            }
        }
    }

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