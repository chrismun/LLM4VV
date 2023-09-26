#include "acc_testsuite.h"
#ifndef T1
//T1:declare directive device_resident clause,V:2.7-3.3
int test1(){
    int err = 0;
    int *a, *b, *c, *d, *e, *f;

    a = (int *)malloc(n * sizeof(int));
    b = (int *)malloc(n * sizeof(int));
    c = (int *)malloc(n * sizeof(int));
    d = (int *)malloc(n * sizeof(int));
    e = (int *)malloc(n * sizeof(int));
    f = (int *)malloc(n * sizeof(int));

    #pragma acc declare device_resident(a, b, c)

    #pragma acc data copy(a[0:n], b[0:n], c[0:n], d[0:n], e[0:n], f[0:n])
    {
        #pragma acc parallel present(a, b, c, d, e, f)
        {
            for (int x = 0; x < n; ++x){
                a[x] = b[x] + c[x];
                d[x] = a[x] * e[x];
                f[x] = d[x] - a[x];
            }
        }
    }

    for (int x = 0; x < n; ++x){
        if (f[x] != (b[x] + c[x]) * e[x] - (b[x] + c[x])){
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