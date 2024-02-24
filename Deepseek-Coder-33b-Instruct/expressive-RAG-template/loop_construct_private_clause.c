#include <stdlib.h>
#include <stdio.h>
#include <openacc.h>

#define N 1000000

int test1(){
    int err = 0;
    int *a = (int*)malloc(N * sizeof(int));
    int i, tmp = 0;

    srand(1234);

    for (i = 0; i < N; i++) {
        a[i] = rand() % 100;
    }

    #pragma acc data copy(a[0:N])
    {
        #pragma acc parallel loop private(tmp)
        for (i = 0; i < N; i++) {
            tmp = a[i];
            a[i] = tmp * 2;
        }
    }

    for (i = 0; i < N; i++) {
        if (a[i] != a[i] * 2) {
            err = 1;
            break;
        }
    }

    free(a);

    return err;
}

int main(){
    int failcode = 0;
    int failed;

    failed = 0;
    for (int x = 0; x < 1; ++x){
        failed = failed + test1();
    }
    if (failed != 0){
        failcode = failcode + (1 << 0);
    }

    return failcode;
}