#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#ifndef T1
//T1:loop construct tile clause,V:2.7-3.3
int test1(){
    int err = 0;
    const int N = 1000;
    int *a = (int*)malloc(N * sizeof(int));
    int *b = (int*)malloc(N * sizeof(int));

    for(int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = 0;
    }

    #pragma acc data copyin(a[:N]) copyout(b[:N])
    {
        #pragma acc parallel loop tile(32)
        for(int i = 0; i < N; i++) {
            b[i] = a[i];
        }
    }

    for(int i = 0; i < N; i++) {
        if(b[i] != a[i]) {
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
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }
#endif
    return failcode;
}