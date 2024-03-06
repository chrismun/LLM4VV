#include "acc_testsuite.h"

#ifndef T1
//T1:compute construct firstprivate clause,V:2.7-3.3
int test1(){
    int err = 0;
    int N = 1000;
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));
    int *c = (int*)malloc(N * sizeof(int));
    int *d = (int*)malloc(N * sizeof(int));

    for (int i = 0; i < N; ++i){
        a[i] = i;
        b[i] = i;
        c[i] = 0;
        d[i] = 0;
    }

    #pragma acc data copyin(a[:N], b[:N]) copyout(c[:N], d[:N])
    {
        #pragma acc parallel loop firstprivate(a, b)
        for (int i = 0; i < N; ++i){
            c[i] = a[i] + b[i];
            d[i] = a[i] - b[i];
        }
    }

    for (int i = 0; i < N; ++i){
        if (c[i] != a[i] + b[i] || d[i] != a[i] - b[i]){
            err++;
        }
    }

    free(a);
    free(b);
    free(c);
    free(d);

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