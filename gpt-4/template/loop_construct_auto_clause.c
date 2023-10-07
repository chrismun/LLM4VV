#include "acc_testsuite.h"
#ifndef T1
//T1:loop construct auto clause,V:2.7-3.3
int test1() {
    int err = 0;
    int n = 1000;
    double *a = (double*)malloc(sizeof(double)*n);
    double *b = (double*)malloc(sizeof(double)*n);
    double *c = (double*)malloc(sizeof(double)*n);

    for(int i=0;i<n;i++)
    {
        a[i] = i;
        b[i] = 2 * i;
    }

    #pragma acc kernels loop copyin(a[:n], b[:n]) copyout(c[:n]) auto
    for(int i = 0; i < n; i++)
    {
        c[i] = a[i] + b[i];
    }

    for(int i = 0; i < n; i++)
    {
        if(c[i] != 3*i){
            err = 1;
        }
    }
    free(a);
    free(b);
    free(c);

    return err;
}
#endif

int main() {
    int failcode = 0;
    int failed;

#ifndef T1
    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x) {
        failed = failed + test1();
    }
    if (failed != 0) {
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}