#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 1000000
#define NUM_TEST_CALLS 10

int test1(){
    int err = 0;
    int *a = (int*)malloc(N*sizeof(int));
    int *b = (int*)malloc(N*sizeof(int));
    int *c = (int*)malloc(N*sizeof(int));

    for(int i = 0; i < N; i++){
        a[i] = i;
        b[i] = i;
        c[i] = 0;
    }

    #pragma acc parallel loop copyin(a[0:N], b[0:N]) copyout(c[0:N])
    for(int i = 0; i < N; i++){
        c[i] = a[i] + b[i];
    }

    for(int i = 0; i < N; i++){
        if(c[i] != 2*i){
            err = 1;
            break;
        }
    }

    free(a);
    free(b);
    free(c);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < NUM_TEST_CALLS; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}