#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:enter data directive,V:2.7-3.3
int test1(){
    int err = 0;
    const int N = 1000;
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));
    int *c = (int*)malloc(N * sizeof(int));

    for (int i = 0; i < N; ++i) {
        a[i] = i;
        b[i] = i;
        c[i] = 0;
    }

    #pragma acc data copyin(a[0:N], b[0:N]) copyout(c[0:N])
    {
        #pragma acc enter data copyin(a[0:N], b[0:N]) create(c[0:N])
        #pragma acc parallel loop
        for (int i = 0; i < N; ++i) {
            c[i] = a[i] + b[i];
        }
        #pragma acc exit data copyout(c[0:N]) delete(a[0:N], b[0:N])
    }

    for (int i = 0; i < N; ++i) {
        if (c[i] != 2 * i) {
            err = 1;
            break;
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
    failed = 0;
    failed = failed + test1();
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}