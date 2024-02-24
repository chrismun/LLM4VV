#include <stdlib.h>
#include <iostream>
#include <openacc.h>

#ifndef T1
//T1:exit data directive,V:2.7-3.3
int test1(){
    int err = 0;
    const int N = 100;
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));

    for(int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc data copyin(a[:N]) copyout(b[:N])
    {
        #pragma acc enter data copyin(a[:N], b[:N])
        #pragma acc parallel loop
        for(int i = 0; i < N; i++) {
            b[i] = a[i];
        }
        #pragma acc exit data copyout(b[:N])
    }

    for(int i = 0; i < N; i++) {
        if(b[i] != i) {
            err = 1;
            break;
        }
    }

    free(a);
    free(b);

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